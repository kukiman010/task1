#include <iostream>
#include <bitset>
#include <string>
#include <map>
#include <list>

using namespace std;
class Frame
{

public:
    enum type_frame
    {
        tf_engine = 0x1,
        tf_armor = 0x2,
        tf_right_arm = 0x4,
        tf_right_arm_weapon = 0x8,
        tf_left_arm = 0x10,
        tf_left_arm_weapon = 0x20,
        tf_right_leg = 0x40,
        tf_wheels = 0x80
    };

    type_frame      get_type()                      {return type;}
    void            set_type(const type_frame & tf) {type = tf;}
private:
    type_frame type;
    // more code
};

class IEngine : public Frame{public: IEngine()  {set_type(Frame::tf_engine);}};
class IArmor : public Frame{public: IArmor()    {set_type(Frame::tf_armor);}};
class IArm : public Frame{public: IArm()        {set_type(Frame::tf_right_arm);}};
class IWeapon : public Frame{public: IWeapon()  {set_type(Frame::tf_right_arm_weapon);}};
class ILegs : public Frame{public: ILegs()      {set_type(Frame::tf_right_leg);}};
class IWheels : public Frame{public: IWheels()  {set_type(Frame::tf_wheels);}};

//template <class... Targs>
class Robot
{
public:
    Robot (uint32_t ut)
    {
        creator();

        uint32_t move_bit =1;
        Frame* dec = nullptr;
        bitset<32> bit(ut);

        for(unsigned int i=0; i<32; ++i)
        {
            map<Frame::type_frame,Frame *>::iterator it = instruction.find( (Frame::type_frame)move_bit );

            if(it->first == move_bit && bit[i] == true)
            {
                dec = it->second;
                modules.push_back(dec);
            }

             move_bit <<=1;
             dec = nullptr;
        }
        tell();
    }

    void shoot(double x, double y) { /* ... */ }
    void move(double x, double y) { /* ... */ }
private:
    // ...
    map<Frame::type_frame,Frame *> instruction;
    list<Frame*> modules;

    void creator(){
        instruction.emplace(Frame::tf_engine ,          new IEngine);
        instruction.emplace(Frame::tf_armor,            new IArmor);
        instruction.emplace(Frame::tf_right_arm,        new IArm);
        instruction.emplace(Frame::tf_right_arm_weapon, new IWeapon);
        instruction.emplace(Frame::tf_left_arm,         new IArm);
        instruction.emplace(Frame::tf_left_arm_weapon,  new IWeapon);
        instruction.emplace(Frame::tf_right_leg,        new ILegs);
        instruction.emplace(Frame::tf_wheels,           new IWheels);
    }

    void tell()
    {
        if(modules.size() != 0)
            std::cout<< "I am alive and I have: " << modules.size() << " details\n";
        else
            cout<< "I'm dead and I have no parts\n";
    }
};


int main()
{
        Robot r(
            Frame::tf_engine
//            | Frame::tf_armor
            | Frame::tf_right_arm
            | Frame::tf_right_arm_weapon
//            | Frame::tf_left_arm
            | Frame::tf_left_arm_weapon
            | Frame::tf_right_leg
//            | Frame::tf_wheels
            );
//        Robot r(0x0);

    return 0;
}
