#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(const string &status = "Human", const string &name = "None") : _name(name), _status(status) {}
    void InitAction() const
    {
        cout << _status << ": " << _name;
    }
    string GetName() const
    {
        return _name;
    }
    string GetProf() const
    {
        return _status;
    }

    //  virtual methods

    virtual void Walk(const string &destination = "somewhere") const
    {
        cout << "Someone walks" << destination << endl;
    };
    virtual ~Human() = default;

protected:
    const string _name;
    const string _status;
};

class Student : public Human
{
public:
    Student(const string &name, const string &favouriteSong) : Human("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() const
    {
        InitAction();
        cout << _name << " learns" << endl;
    }

    void Walk(const string &destination) const override
    {
        InitAction();
        cout << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const
    {
        InitAction();
        cout << " sings a song: " << FavouriteSong << endl;
    }

public:
    const string FavouriteSong;
};

class Teacher : public Human
{
public:
    Teacher(const string &name, const string &subject) : Human("Teacher", name), Subject(subject) {}

    void Teach() const
    {
        InitAction();
        cout << " teaches: " << Subject << endl;
    }

    void Walk(const string &destination) const override
    {
        InitAction();
        cout << " walks to: " << destination << endl;
    }

public:
    const string Subject;
};

class Policeman : public Human
{
public:
    Policeman(const string &name) : Human("Policeman", name) {}

    void Check(const Human &pers) const
    {
        InitAction();
        cout << " checks " << pers.GetProf() << ". " << pers.GetProf() << "'s name is: " << pers.GetName() << endl;
    }

    void Walk(const string &destination) const override
    {
        InitAction();
        cout << " walks to: " << destination << endl;
    }
};

void VisitPlaces(const Human &pers, const vector<string> &places)
{
    for (const auto &p : places)
    {
        pers.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
