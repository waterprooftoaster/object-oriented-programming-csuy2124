/*
  rec10_start.cpp
  Starting code 23S
 */

#include <ostream>
#include <iostream>
#include <iostream>
#include <vector>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void normalPlay() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual ~Instrument() = default;

};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}


class Percussion : public Instrument {
public:
    // using Instrument::Instrument;
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion {
    // using Percussion::Percussion;
    void normalPlay() const override { cout << "Boom"; }
    void print(ostream& os) const override { os << "Drum"; }
};

class Cymbal : public Percussion {
    using Percussion::Percussion;
    void normalPlay() const override { cout << "Crash"; }
    void print(ostream& os) const override { os << "Cymbal"; }
};

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }

    int getMouthpiece () const{
        return mouthpiece;
    }

private:
    int mouthpiece;
};

class Trombone : public Brass {
    using Brass::Brass;
    void normalPlay() const override { cout << "Blat"; }
    void print(ostream& os) const override { os << "Trombone: " << getMouthpiece();; }
};

class Trumpet : public Brass {
    using Brass::Brass;
    void normalPlay() const override { cout << "Toot"; }
    void print(ostream& os) const override { os << "Trumpet: " << getMouthpiece(); }
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }

    int getPitch() const {return pitch;}

private:
    int pitch;
};

class Cello : public String {
    using String::String;
    void normalPlay() const override { cout << "Squawk"; }
    void print(ostream& os) const override { os << "Cello: " << getPitch(); }
};

class Violin : public String {
    using String::String;
    void normalPlay() const override { cout << "Screech"; }
    void print(ostream& os) const override { os << "Violin:" << getPitch(); }
};

class MILL {
public:
    friend ostream& operator<<(ostream& os, const MILL& a_mill) {
        os << "The MILL has the following instruments:";
        if (a_mill.inventory.empty()) {
            os << " None" << endl;
            return os;
        }

        for (const Instrument* instr : a_mill.inventory) {
            if (instr) {
                os << "\n\t";
                instr->print(os);
            }
        }
        os << endl;
        return os;
    }
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for (Instrument*& instrp : inventory) {
            if (!instrp) {
                instrp = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    void dailyTestPlay() const {
        for (const Instrument* instrp : inventory) {
            if (instrp) {
                instrp->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (Instrument*& instrp : inventory) {
            if (instrp) {
                Instrument* result(instrp);
                instrp = nullptr;
                return result;
            }
        }
        return nullptr;
    }

private:
    vector<Instrument*> inventory;
};

class Musician {
public:
    Musician(const string& musicianName) : instr(nullptr), name(musicianName) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr)
            instr->makeSound();
        else
            cerr << "have no instr\n";
    }

    void play() const {
        if (instr) {
            instr->normalPlay();
        }
    }

private:
    string name;
    Instrument* instr;
};

class Orch {
public:
    void addPlayer(Musician& member) { members.push_back(&member); }
    void play() const {
        for (Musician* member : members) {
            member->play();
        }
        cout << endl;
    }

private:
    vector<Musician*> members;
};

int main() {
    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
            << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay(); // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;

    mill.dailyTestPlay();

    cout << endl;

    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;


    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}
