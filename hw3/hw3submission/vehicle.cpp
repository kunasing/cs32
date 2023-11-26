// VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE VEHICLE
class Vehicle{
public:
    Vehicle(string id){   m_id = id;}
    virtual bool canHover() const;
    virtual string description () const = 0;
    string id() const {     return m_id;}
    virtual ~Vehicle(){};
private:
    string m_id;
};

bool Vehicle::canHover() const{
    if (this->description() == "a satellite")
        return false;
    return true;
};




// DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE DRONE
class Drone: public Vehicle{
public:
    Drone(string id):Vehicle(id){}
    virtual string description () const {   return "a drone";}
    virtual ~Drone(){   cout << "Destroying " << id() << ", a drone" << endl;}
};



// BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON BALLOON
class Balloon: public Vehicle{
public:
    Balloon(string id, double size):Vehicle(id), m_size(size){}
    virtual string description () const;
    virtual ~Balloon(){   cout << "Destroying the balloon " << id() << endl;}
private:
    double m_size;
};


string Balloon::description () const{
    if (m_size < 8)
        return "a small balloon";
    return "a large balloon";
}



// SATELLITE SATELLITE SATELLITE SATELLITE SATELLITE SATELLITE SATELLITE SATELLITE SATELLITE
class Satellite: public Vehicle{
public:
    Satellite(string id):Vehicle(id){}
    virtual string description () const{   return "a satellite";}
    virtual ~Satellite(){   cout << "Destroying the satellite " << id() << endl;}
};

