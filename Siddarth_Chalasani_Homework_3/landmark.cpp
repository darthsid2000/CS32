class Landmark {
public:
    Landmark(string useful) {
        m_name = useful;
    }
    
    virtual ~Landmark() {
        cout << m_name << "." << endl;
    }
    
    string name() const {
        return m_name;
    }
    
    virtual string color() const {
        return "yellow";
    }
    
    virtual string icon() const = 0;
    
private:
    string m_name;
};

class Hotel: public Landmark {
public:
    Hotel(string name) : Landmark(name) {}
    
    virtual ~Hotel() {
        cout << "Destroying the hotel ";
    }
    
    virtual string icon() const {
        return "bed";
    }
};

class Restaurant: public Landmark {
public:
    Restaurant(string name, int size) : Landmark(name) {
        m_size = size;
    }
    
    virtual ~Restaurant() {
        cout << "Destroying the restaurant ";
    }
    
    virtual string icon() const {
        if (m_size < 40)
            return "small knife/fork";
        return "large knife/fork";
    }
    
private:
    int m_size;
};

class Hospital: public Landmark {
public:
    Hospital(string name) : Landmark(name) {}
    
    virtual ~Hospital() {
        cout << "Destroying the hospital ";
    }
    
    virtual string color() const {
        return "blue";
    }
    
    virtual string icon() const {
        return "H";
    }
};
