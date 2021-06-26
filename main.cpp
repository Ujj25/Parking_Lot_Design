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
    map<string,string> cmd_to_func;
    map<string,string> spl_var;
    bool flag = 0;


    public:


    void initialize()
    {
        // "?" - Registration Number
        // "*" - Age
        // "#" - Slot Number
        // "$" - Number of Slots

        spl_var["?"] = "regNo";
        spl_var["*"] = "age";
        spl_var["#"] = "slotNo";
        spl_var["$"] = "number_of_slots";

        string cmd1 = "Create_parking_lot $";
        string cmd2 = "Park ? driver_age *";
        string cmd3 = "Slot_numbers_for_driver_of_age *";
        string cmd4 = "Slot_number_for_car_with_number ?";
        string cmd5 = "Leave #";
        string cmd6 = "Vehicle_registration_number_for_driver_of_age *";

        cmd_to_func[cmd1] = "createParking";
        cmd_to_func[cmd2] = "park";
        cmd_to_func[cmd3] = "slot_numbers_from_age";
        cmd_to_func[cmd4] = "slot_numbers_from_reg_number";
        cmd_to_func[cmd5] = "leave";
        cmd_to_func[cmd6] = "reg_number_from_age";

    }

    vector<string> convertToWord(string str)
    {
        vector<string> words;
        string word = "";
        for (auto x : str)
        {
            if (x == ' ')
            {
                words.push_back(word);
                word = "";
            }
            else
            {
                word = word + x;
            }
        }
        words.push_back(word);
        return words;

    }

    void map_to_func(string inp)
    {
        string func = "";
        vector<string> str_cmd;
        vector<string> str_inp;
        for(auto it = cmd_to_func.begin(); it != cmd_to_func.end(); it++)
        {
            string cmd = it->first;
            str_cmd = convertToWord(cmd);
            str_inp = convertToWord(inp);
            if(str_cmd.size() == str_inp.size())
            {
                //cout<<cmd<<endl;
                bool check = 0;
                int i;
                for(i = 0; i < str_cmd.size(); i++)
                {
                    if(str_cmd[i] == str_inp[i])
                        continue;
                    else
                    {
                        bool fl = 0;
                        for(auto it1 = spl_var.begin(); it1 != spl_var.end(); it1++)
                        {
                            if (it1->first == str_cmd[i])
                            {
                                //cout<<it->
                                fl = 1;
                                break;
                            }
                        }
                        if(fl == 0)
                            break;
                    }
                }
                if(i == str_cmd.size())
                {
                    func = it->second;
                    break;
                }
            }
            else
                continue;

        }
        //cout<<func<<endl;
        
        if(func == "createParking")
        {
            string str = str_inp[1];
            int sz = stoi(str);
            createParking(sz);
            return;
        }
        if(func == "park")
        {
            string str = str_inp[1];
            string age = str_inp[3];
            int a = stoi(age);
            park(str,a);
            return;
        }
        if(func == "slot_numbers_from_age")
        {   
            //cout<<"newnew124124"<<endl;
            
            string str = str_inp[1];
            int age = stoi(str);
            vector<int> slot_numbers_from_age = getSlotNumbersFromAge(age);
            return;
        }
        if(func == "leave")
        {
            string str = str_inp[1];
            int slot = stoi(str);
            leave(slot);
            return;
        }
        if(func == "reg_number_from_age")
        {
          //cout<<"newqw\n";

            string str = str_inp[1];
            int age = stoi(str);
            vector<string> x = getRegistrationNumbersFromAge(age,1);
            return;
        }
        if(func == "slot_numbers_from_reg_number")
        {
            
            string str = str_inp[1];
            int slot_number_from_reg_number = getSlotNumberFromRegNo(str);
            return;
        }
        
        // end
    }

    void Print(int val)
    {
        cout<<val<<endl;
    }

    void Print(vector<int> val)
    {
        //cout<<"!!#!#"<<endl;
        
        for(int i = 0; i < val.size(); i++)
        { 
          if(i==val.size()-1)
            cout<<val[i]<<" ";
          else
            cout<<val[i]<<",";
            
        }
        cout<<endl;
    }
    void Print(vector<string> val)
    {
        for(int i = 0; i < val.size(); i++)
        {
            if(i==val.size()-1)
              cout<<val[i]<<" ";
            else
              cout<<val[i]<<",";
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
            cout<<"Car with vehicle registration number \""<<regNo <<"\" has been parked at slot number "<<slot<<endl;
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
            cout<<"Slot number "<<slotNo<<" vacated, the car with vehicle registration number \"";
            
            mp1.erase(slotNo);
            slotList.insert(slotNo);
            string regNo = carToLeave.first;

            cout<<regNo<<"\" left the space, the driver of the car was of age ";

            int age = carToLeave.second;
            cout<<age<<endl;

            mp3[age].erase(mp3[age].find(regNo));
            mp2.erase(regNo);

            
        }
    }

    vector<string> getRegistrationNumbersFromAge(int age,bool p)
    { 
      //cout<<"asda";

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
        // else
        //     cout << "Not found" << endl;
        
        if(p)
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
            vector<string> RegNoFromAge = getRegistrationNumbersFromAge(age,0);
            for (int j = 0; j < RegNoFromAge.size(); j++)
            {
                SlotNoFromAge.push_back(mp2[RegNoFromAge[j]]);
            }
        }
        // else
        //     cout << "Not found" << endl;

        //cout<<"new!@!#!#!";
        
        Print(SlotNoFromAge);
        return SlotNoFromAge;

    }

    int getSlotNumberFromRegNo(string regNo)
    {
        //cout<<"newe!#!#";
        
        if(!flag)
        {
            cout<<"Parking Lot is not created, yet\n";
            return -1;
        }
        if(mp2.find(regNo) != mp2.end())
        {
            //cout<<"!#!\n";
            
            Print(mp2[regNo]);
            return mp2[regNo];
        }

        // else
        //     cout<<"Not found"<<endl;

        return 0;
    }

};


int main()
{
        #ifndef ONLINE_JUDGE
        freopen("input.txt", "r" ,stdin);
        freopen("output.txt", "w" ,stdout);
        #endif

        // cout<<"===================================================================\n";
        // cout<<"\t\tWelcome to a Parking Lot System"<<endl;
        // cout<<"===================================================================\nEnter below commands: ([] represents input)\n";
        

        int size;
        //cin>>size;
        //cout<<size;

        ParkingLot P1;
        P1.initialize();
        string inp;

        while(1){
            getline(cin,inp);
            
            if(inp == "")
              break;

            P1.map_to_func(inp);
        }
        
        return 0;
}