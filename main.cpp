#include<bits/stdc++.h>
using namespace std;

// bool checkforslot
// giveslot
// leaveslot
// retrieveSlotNuberAge
// retrieveSlotRegNumber
// retrieveVehicleNumberAge

class ParkingLot
{

    set<int> slotList;   // slots list

    map<int,pair<string,int>> mp1;    //slot,<regNo,age>
    map<string,int> mp2;                 //regNo,slot
    map<int,set<string>> mp3;         //age,list of regNo
    bool flag = 0;
    
    int max_size=0;

    public:

        void Print(int val)
        {
            cout<<val<<endl;
        }
        
        void Print(vector<int> val)
        {
            for(int i = 0; i < val.size(); i++)
            {
                cout<<val[i]<<" ";
            }
            cout<<endl;
        }
        void Print(vector<string> val)
        {
            for(int i = 0; i < val.size(); i++)
            {
                cout<<val[i]<<" ";
            }
            cout<<endl;
        }

        void createParking(int sz){
            if(sz > 0)
                flag = 1;
            for(int i = 1; i <= sz; i++)
            {
                slotList.insert(i);
            }
            cout<<"Created parking of "<<sz<<" slots"<<endl;
        }

        void park(string regNo,int age){
            if(!flag)
            {
                cout<<"Parking Lot is not created, yet\n";
                return;
            }
            if(slotList.size() == 0)
            {
                cout<<"Parking Full\n";
            }
            else
            {
                int slot = *slotList.begin();
                mp1[slot]={regNo,age};
                mp2[regNo]=slot;
                mp3[age].insert(regNo);
                cout<<"Allocated slot number: "<<slot<<endl;
                slotList.erase(slotList.begin());
            }
        }

        void leave(int slotNo)
        {
            if(!flag)
            {
                cout<<"Parking Lot is not created, yet\n";
                return;
            }
            if(slotList.find(slotNo) != slotList.end())
            {
                cout<<"Slot is already empty\n";
            }
            else
            {
                pair<string,int> carToLeave = mp1[slotNo];
                mp1.erase(slotNo);
                slotList.insert(slotNo);
                string regNo = carToLeave.first;
                int age = carToLeave.second;
                mp3[age].erase(mp3[age].find(regNo));
                mp2.erase(regNo);
                
            }
        }

        vector<string> getRegistrationNumbersFromAge(int age)
        {
            vector<string> RegNoFromAge;
            if(!flag)
            {
                cout<<"Parking Lot is not created, yet\n";
                return RegNoFromAge;
            }
            if(mp3.find(age) != mp3.end())
            {
                set<string> regNoList = mp3[age];
                for (auto it = regNoList.begin(); it != regNoList.end(); it++)
                {
                    RegNoFromAge.push_back(*it);
                    
                }
            }
            else
                cout << "Not found" << endl;
            Print(RegNoFromAge);
            return RegNoFromAge;
            
	    }

        vector<int> getSlotNumbersFromAge(int age)
        {
            vector<int> SlotNoFromAge;
            if(!flag)
            {
                cout<<"Parking Lot is not created, yet\n";
                return SlotNoFromAge;
            }
            if (mp3.find(age) != mp3.end())
            {
                vector<string> RegNoFromAge = getRegistrationNumbersFromAge(age);
                for (int j = 0; j < RegNoFromAge.size(); j++)
                {
                    SlotNoFromAge.push_back(mp2[RegNoFromAge[j]]);
                }
            }
            else
                cout << "Not found" << endl;
            Print(SlotNoFromAge);
            return SlotNoFromAge;

        }

        int getSlotNumberFromRegNo(string regNo)
        {
            if(!flag)
            {
                cout<<"Parking Lot is not created, yet\n";
                return -1;
            }   
            if(mp2.find(regNo) != mp2.end())
            {
                
                Print(mp2[regNo]);
                return mp2[regNo];
            }

            else
                cout<<"Not found"<<endl;

            return 0;
            
        }

};


int main()
{
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r" ,stdin);
    // freopen("output.txt", "w" ,stdout);
    // #endif

    cout<<"Welcome to a Parking Lot System"<<endl;

    int size;
    cin>>size;
    //cout<<size;
    ParkingLot P1;

    P1.createParking(size);
    P1.park("abcd", 20);
    P1.park("abcd2", 21);
    P1.park("kkjkl",21);
    P1.getSlotNumbersFromAge(21);
    P1.park("absd",40);
    P1.getRegistrationNumbersFromAge(21);
    P1.getSlotNumberFromRegNo("abcd");
    
}