#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <cctype>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_dna;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_dna = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    genomes.clear();
    string name;
    string dna;
    string temp;
    while (getline(genomeSource, temp)) {
        if (temp.empty())
            return false;
        if (temp[0] == '>') {
            if (name.empty() != dna.empty() || temp.size() < 2)
                return false;
            if (!name.empty()) {
                Genome gnm(name, dna);
                genomes.push_back(gnm);
                name = "";
                dna = "";
            }
            for (int i = 1; i < temp.size(); i++)
                name += temp[i];
            continue;
        }
        if (name.empty() || temp.size() > 80)
            return false;
        for (int i = 0; i < temp.size(); i++)
            switch (toupper(temp[i])) {
                case 'A':
                case 'C':
                case 'T':
                case 'G':
                case 'N':
                    dna += toupper(temp[i]);
                    break;
                default:
                    return false;
            }
    }
    if (dna.empty())
        return false;
    Genome gnm(name, dna);
    genomes.push_back(gnm);
    return true;
}

int GenomeImpl::length() const
{
    return m_dna.size();
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position < 0 || length < 0 || position + length > m_dna.size())
        return false;
    fragment = "";
    for (int i = position; i < position + length; i++)
        fragment += m_dna[i];
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
