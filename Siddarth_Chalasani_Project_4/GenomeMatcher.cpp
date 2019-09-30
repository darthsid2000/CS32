#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool orderMatch(const GenomeMatch& lhs, const GenomeMatch& rhs) {
    if (lhs.percentMatch > rhs.percentMatch || (lhs.percentMatch == rhs.percentMatch && lhs.genomeName < rhs.genomeName))
        return true;
    return false;
}

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    vector<Genome> m_genomes;
    
    struct TrieFragment {
        TrieFragment(int index, int pos) {
            m_index = index;
            m_pos = pos;
        }
        bool operator<(const TrieFragment& rhs) const {
            if (m_index < rhs.m_index || (m_index == rhs.m_index && m_pos < rhs.m_pos))
                return true;
            return false;
        }
     
        int m_index;
        int m_pos;
    };
    
    Trie<TrieFragment> m_trie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.push_back(genome);
    for (int i = 0; i <= genome.length() - m_minSearchLength; i++) {
        string fragment;
        genome.extract(i, m_minSearchLength, fragment);
        TrieFragment insert(m_genomes.size() - 1, i);
        //cout << m_genomes[insert.m_index].name() << " at position " << insert.m_pos << endl;
        m_trie.insert(fragment, insert);
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    matches.clear();
    if (fragment.size() < minimumLength || minimumLength < m_minSearchLength)
        return false;
    string key;
    int track = 0;
    for (; track < m_minSearchLength; track++)
        key += fragment[track];
    std::vector<TrieFragment> trieFrags = m_trie.find(key, exactMatchOnly);
    sort(trieFrags.begin(), trieFrags.end());
    for (int i = 0; i < trieFrags.size(); i++) {
        int maxLength = 0;
        TrieFragment* temp = nullptr;
        int genomeIndex = trieFrags[i].m_index;
        while (i < trieFrags.size() && trieFrags[i].m_index == genomeIndex) {
            int length = 0;
            int mismatches = 0;
            for (int j = 0; j < fragment.size(); j++) {
                string tempFrag;
                if (m_genomes[genomeIndex].extract(j+trieFrags[i].m_pos, 1, tempFrag)) {
                    if (tempFrag[0] == fragment[j])
                        length++;
                    else if (!exactMatchOnly && mismatches < 1) {
                        mismatches++;
                        length++;
                    }
                    else
                        break;
                }
                else
                    break;
            }
            
            if (length > maxLength) {
                maxLength = length;
                temp = &trieFrags[i];
            }
            
            i++;
        }
        if (maxLength >= minimumLength) {
            DNAMatch match;
            match.genomeName = m_genomes[temp->m_index].name();
            match.position = temp->m_pos;
            match.length = maxLength;
            matches.push_back(match);
        }
    }
    return !matches.empty();
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_minSearchLength)
        return false;
    results.clear();
    unordered_map<string, int> map;
    int S = query.length() / fragmentMatchLength;
    for (int i = 0; i < S; i++) {
        string fragment;
        query.extract(i*fragmentMatchLength, fragmentMatchLength, fragment);
        vector<DNAMatch> matches;
        if (findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, matches))
            for (int j = 0; j < matches.size(); j++)
                map[matches[j].genomeName]++;
    }
    
    for (unordered_map<string, int>::iterator it = map.begin(); it != map.end(); it++) {
        double matchPercent = it->second / S;
        if (matchPercent >= matchPercentThreshold) {
            GenomeMatch match;
            match.genomeName = it->first;
            match.percentMatch = it->second;
            results.push_back(match);
        }
    }
    sort(results.begin(), results.end(), orderMatch);
    return !results.empty();
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
