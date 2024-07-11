#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;


#define MAXRAD 50
struct Radiology{
    string fname;
    string lname;
    int expyear;
    int room_nb;
    int patient_nb;
    string type;  //type of rad (MRI || CT || PET)
    int radnb; //counter;
} ;

void InitializeRadiology(Radiology *);
bool RadiologyisFull(Radiology*);
bool RadiologyisEmpty(Radiology*);
void readRadiologyData(Radiology*,string,string,int,int,int ,string);
void printRad(Radiology *);
void BookRadiologyScan(Radiology*);
Radiology *searchRadiologist(Radiology*,string);
void SortByYearofExperience(Radiology *);
void swap(Radiology *,Radiology*);





class Appointment{
public:
    string appointment;
    int day;
    int month;
    int hour;
    int min;


    static void appointmentToString(fstream& a, int day, int month, int hour, int min);
    static void AvailableAppointments();
    static void SpecificDoctorAppointment();


    struct appointments{
        string date;
        appointments *next;

    };
};

struct Doctor {
    string fname;
    string lname;
    int age;
    string specialization;
    Appointment appointment;

    Doctor *next;
};

struct MedicalHistory{
    bool allergie;
    string allergirtype;
    bool medication;
    string description;

};

struct Patient{
    string fullName;
    int id;
    int ins_nb;
    int age;
    string bloodType;

    Patient* next;

    MedicalHistory MH;
};



void DeleteAppointment(Doctor*,int);

void printListPatient(){
    cout<<"1-See List of Doctors\n";
    cout<<"2-Take an appointment\n";
    cout<<"3-See Available Appointments\n";
    cout<<"4-Search for a List of Doctors by Specialization\n";
    cout<<"5-Search Doctor by name\n";
    cout<<"6-Delete an Appointment\n";
    cout<<"7-Go to radiology section\n";
    cout<<"8-Exit\n";
    cout<<">>";
}

void printListRadiology(){
    cout<<endl;
    cout<<"1-Radiologist List\n";
    cout<<"2-Book A radiology Scan\n";
    cout<<"3-Sort Radiologist by Year of Experience\n";
    cout<<"4-Previous Menu\n";
    cout<<">>";

}

void printListDoctor(){
    cout<<endl;
    cout<<"1-Patients List\n";
    cout<<"2-Add Patient Medical History\n";
    cout<<"3-View My Appointments\n";
    cout<<"4-List of Patients with Specific Blood Type\n";
    cout<<"5-Exit\n";
    cout<<">>";
}


void Login();
void PatientCase(Radiology *);
void radiologyCase(Radiology *);
void DoctorCase(Doctor*);


void addDoctor(fstream &,Doctor *&,string,string,int,string);
Doctor *InitializeList();
bool isEmpty(Doctor *);
void printDoctor(Doctor *);
bool searchDoctor(Doctor*,string);
Doctor FindDoctor(Doctor*,string);

void searchDoctorSpecialization(Doctor *,string  );
void searchDoctorByName(Doctor*,string);

void MedicalHistory(Patient*);


void addPatient(fstream& ,Patient *&,string,int,int,string);
Patient *InitializepatientList();
bool patientisEmpty(Patient *);
void printPatient(Patient *);
void PatientRegistration();
bool searchPatient(Patient*,string,int);
void PatientBloodType(Patient*,string);

void setAppointment(Doctor*&, int,int,int,int,string);
bool AppointmentExist(Doctor*, int ,int,int,int);
void TakeAppointment();


Patient *patient;
Doctor *doctor;

fstream p("patient.txt", ios::in | ios::out | ios::app);
fstream a("appointment.txt", ios::in | ios::out | ios::app);
fstream d("doctor.txt", ios::in | ios::out | ios::app);
int main(){

    //fstream p("patient.txt", ios::in | ios::out | ios::app);

    doctor = InitializeList();
    patient = InitializepatientList();
    Radiology *rad = new Radiology[MAXRAD];
    InitializeRadiology(rad);
    readRadiologyData(rad,"April","Barlow",13,4,5,"MRI");
    readRadiologyData(rad,"Luna","Crosby",3,3,5,"MRI");
    readRadiologyData(rad,"Ivan","Dunn",10,4,5,"CT");
    readRadiologyData(rad,"Roy","Baxter",7,8,5,"PET");
    // printRad(rad);


    addPatient(p,patient,"Neil Mccoy",233,55,"O+");
    addPatient(p,patient,"zeinabIbrahim",334,56,"AB+");
    addPatient(p,patient,"PatientName",344,58,"O+");

    addDoctor(d,doctor, "DrWilliam","Abdu", 40, "Orthopedics");
    addDoctor(d,doctor, "DrMyles","Johnson", 54, "Cardiologists");
    addDoctor(d,doctor, "DrMark","Smith", 32, "Cardiologists");
    addDoctor(d,doctor, "DrMona","Davis", 56, "Neurologists");


    setAppointment(doctor,2,3,10,30,"DrMona");
    setAppointment(doctor,4,5,12,40,"DrMark");


    //Appointment appointment;
    //appointment.AvailableAppointments();


    searchDoctorSpecialization(doctor,"Cardiologists");
    cout<<"\n\n\t\t\t-----------------------Hospital Manegment System------------------\n\n\n";


    cout<<endl;

    int option;
    string drname;
    bool drfound = false;
    cout<<"1-Patient\n2-Doctor\n";
    do {
        cout << ">";
        cin >> option;
    }while(option < 1 || option > 2);

    switch(option){
        case 1:
            Login();
            cout<<"\n---------------------WELCOME "<<patient->fullName<<"------------------------------\n\n";
            PatientCase(rad);
            break;

        case 2:

            do{
                cout<<"\nPlease Enter Your Name : ";
                cin>>drname;
                drfound = searchDoctor(doctor,drname);
            }while(drfound ==false);

            DoctorCase(doctor);

            break;
    }






    addPatient(p,patient,"Angelo Cooper",2683,849,"AB+");
    addPatient(p,patient,"Lesly Greene",233,456,"O+");
    // printPatient(patient);
    p.close();
    a.close();
    d.close();

    return 0;
}


void Login(){
    int r;
    cout<<"1-Register\n2-Already have a File at Hospital\n";
    do{
        cout<<">";
        cin>>r;
    }while(r < 1 || r > 2);

    switch(r){
        case 1:
            PatientRegistration();
            break;

        case 2:
            string name;
            int id;
            cout<<"Please Enter your name and ID :"<<endl;
            cout<<"Full Name :";
            cin>>name;
            cout<<"ID : ";
            cin>>id;
            if(searchPatient(patient,name,id)){
                cout<<"Loading....\n";
            }else{
                cout<<"You are not registered yet!\n Please Enter your information to Open a File at the Hospital\n\n";
                PatientRegistration();
            }

            break;
    }


}

void PatientCase(Radiology *rad){


    Appointment app;

    printListPatient();
    string specialization;
    string drname;
    int month;
    int n;
    do{
        cin>>n;
        switch(n){
            case 1:
                printDoctor(doctor);
                break;

            case 2:
                TakeAppointment();
                break;

            case 3:

                app.AvailableAppointments();

                break;

            case 4:

                cout<<"Enter specialization (Cardiologists - Neurologists - Orthopedics - )"<<endl;
                cout<<">>";
                cin>> specialization;

                searchDoctorSpecialization(doctor,specialization);
                break;

            case 5:
                cout<<"Enter Name of Doctor you are searching for:";
                cin>>drname;
                searchDoctorByName(doctor,drname);
                break;

            case 6:

                cout<<"Enter The month of the Appointment you want to delete :";
                cin>>month;
                DeleteAppointment(doctor,month);
                break;

            case 7:
                cout<<"\n\n---------------------RADIOLOGY SECTION---------------------------\n\n";
                radiologyCase(rad);
                break;

            case 8:
                cout<<"Exit..."<<endl;
                break;
        }

        printListPatient();
        cout<<endl;
        cout<<endl;


    }while(n<9);
}


void radiologyCase(Radiology *rad){

    int nrad;

    do{
        cin>>nrad;
        switch(nrad){
            case 1:
                cout<<endl;
                printRad(rad);

                break;

            case 2:
                BookRadiologyScan(rad);
                break;

            case 3:
                SortByYearofExperience(rad);
                break;

            case 4:
                break;
        }

        printListRadiology();
        cout<<endl;
        cout<<endl;
    }while(nrad < 4);

}

void DoctorCase(Doctor *doctor){

    int ndr;
    string bloodType;
    printListDoctor();
    Appointment appointment;

    do{
        cin>>ndr;
        switch(ndr){
            case 1:
                cout<<endl;
                printPatient(patient);

                break;

            case 2:
                MedicalHistory(patient);
                break;

            case 3:
                appointment.SpecificDoctorAppointment();
                break;

            case 4:
                cout<<"Enter Blood Type : ";
                cin>>bloodType;
                PatientBloodType(patient,bloodType);
                break;

            case 5:
                cout<<"Exit..."<<endl;
                break;


        }

        printListDoctor();
        cout<<endl;
        cout<<endl;
    }while(ndr < 6);

}




void addDoctor(fstream& d,Doctor *&doctor, string name, string last, int age, string spec){
    Doctor *temp;
    temp = new Doctor;
    if(temp == NULL){
        exit(1);
    }

    temp->fname = name;
    temp->lname = last;
    temp->specialization = spec;
    temp->age = age;

    temp->next = doctor;
    doctor = temp;

d<<temp->fname<<"\t\t\t"<<temp->lname<<"\t\t\t"<<temp->specialization<<endl;

}

Doctor *InitializeList(){
    return NULL;
}

bool isEmpty(Doctor *doctor){
    return (doctor == NULL);
}

void printDoctor(Doctor *doctor){
    Doctor *cur;
    if(isEmpty(doctor))
    {
        cout<<"The List of Doctors is Empty!"<<endl;
        return;
    }
    else{
        int i = 1;
        cout<<"List of Doctors :"<<endl;
        cout<<"Doctor\t\tFirst name\t\tLast name\t\tspecialization\n";
        cur = doctor;
        while(cur != NULL){
            cout<<i<<"\t\t"<<cur->fname<<"\t\t\t"<<cur->lname<<"\t\t\t"<<cur->specialization<<endl;
            cur = cur->next;
            i++;
        }
    }

}




void addPatient(fstream& f,Patient *&patient, string fullname,int ins_nb, int id, string blood){
    Patient *temp;
    temp = new Patient;
    if(temp == NULL){
        exit(1);
    }

    temp->fullName = fullname;
    temp->ins_nb = ins_nb;
    temp->id = id;
    temp->bloodType = blood;

    temp->next = patient;
    patient = temp;

    f <<  setw(5) << temp->fullName << setw(5) << temp->ins_nb << setw(5)<<temp->id<<setw(5)<<temp->bloodType<<endl;
}

Patient *InitializepatientList(){
    return NULL;
}

bool patientisEmpty(Patient *patient){
    return (patient == NULL);
}

void printPatient(Patient *patient){
    Patient *cur;
    if(patientisEmpty(patient))
    {
        cout<<"The List of Patients is Empty!"<<endl;
        return;
    }
    else{
        int i = 1;
        cout<<"List of Patients :"<<endl;
        cout<<"Patient\t\tFull Name\t\tID\t\tInsurance nb\t\tBlood Type\n";
        cur = patient;
        while(cur != NULL){
            cout<<i<<"\t\t"<<cur->fullName<<"\t\t"<<cur->id<<"\t\t"<<cur->ins_nb<<"\t\t\t"<<cur->bloodType<<endl;
            cur = cur->next;
            i++;
        }
    }

}

void PatientRegistration(){
    string fullName;
    int Ins;
    string blood;
    cout<<"Patient Full Name :";
    cin>>fullName;

    do{
        cout<<"Insurance number : ";
        cin>>Ins;
    } while(Ins < 1);

    do{
        cout<<"Blood Type :";
        cin>>blood;
    }while(blood.compare("O+") != 0 && blood.compare("AB+") != 0 && blood.compare("AB-") != 0 && blood.compare("O-") != 0
           && blood.compare("A-") != 0 && blood.compare("A+") != 0 && blood.compare("B-") != 0 && blood.compare("B+") != 0);

    int id = rand()% 1000 +2;

    addPatient(p,patient,fullName,Ins,id,blood);

    cout<<"Patient Registered Succefully!\n";


}

bool searchPatient(Patient *patient,string name, int id ){
    Patient *cur = patient;
    while(cur != NULL){
        if((cur->fullName).compare(name) == 0 && cur->id == id){

            cout<<"Loged in succefully!\n\n";
            return true;
        }

        cur = cur->next;
    }

    return false;

}

void setAppointment(Doctor *&doctor, int day,int month, int hour, int min,string drname){
    if(day < 1 || day > 7){
        day = 1;
    }
    if(month < 1 || month > 12){
        month = 1;
    }
    if(hour < 1 || hour > 23){
        hour = 2;
    }
    if(min < 0 || min > 60){
        min = 30;
    }

    doctor->appointment.day =day;
    doctor->appointment.month = month;
    doctor->appointment.hour = hour;
    doctor->appointment.min = min;


    cout<<"Your Appointment has been set Succefully !\n\n";
    cout<<"Appointment info\n";
    *doctor = FindDoctor(doctor,drname);
    cout<<drname<<"->\t";
    Appointment::appointmentToString(a,day,month,hour,min);
}

void Appointment::appointmentToString(fstream& a,int day,int month,int hour, int min){
    string sday;
    string smonth;


    switch (day) {
        case 1:
            sday ="Monday";
            break;
        case 2:
            sday ="Tuesday";
            break;
        case 3:
            sday ="Wednesday";
            break;
        case 4:
            sday ="Thursday";
            break;
        case 5:
            sday="Friday";
            break;

        case 6:
            sday ="Saturday";
            break;

        case 7:
            sday="Sunday";
            break;

    }



    switch(month){
        case 1:
            smonth="January";
            break;

        case 2:
            smonth="February";
            break;

        case 3:
            smonth="March";
            break;

        case 4:
            smonth="April";
            break;

        case 5:
            smonth="May";
            break;

        case 6:
            smonth="June";
            break;

        case 7:
            smonth="July";
            break;

        case 8:
            smonth="August";
            break;
        case 9:
            smonth="September";
            break;
        case 10:
            smonth="October";
            break;
        case 11:
            smonth="November";
            break;
        case 12:
            smonth="December";
            break;
    }
    int year = 2022;

    string am;
    if(1< hour < 7){
        am ="PM";
    }
    else{
        am = "AM";
    }

    cout<<sday<<", "<<smonth<<" ,"<< year <<"\tAt\t"<<hour<<" : "<<min<<am<<endl;
    cout<<"Please save the date : "<<day<<"/"<<month<<"/"<<year<<"\tTime - "<<hour<<" : "<<min<<am<<endl;

a<< sday<<", "<<smonth<<" ,"<< year <<"\tAt\t"<<hour<<" : "<<min<<am<<endl;
}

bool AppointmentExist(Doctor *doctor,int day,int month,int hour,int min){
    Doctor* cur=doctor;
    if(isEmpty(doctor))
        return false;
    while(cur!=NULL){
        if(cur->appointment.day == day && cur->appointment.month == month && cur->appointment.hour== hour)
            return true;
        cur=cur->next;
    }
    return false;

}


bool searchDoctor(Doctor *doctor,string name ){
    Doctor *cur = doctor;
    while(cur != NULL){
        if((cur->fname).compare(name) == 0){
            return true;
        }

        cur = cur->next;
    }

    return false;

}

Doctor FindDoctor(Doctor* doctor,string name){
    searchDoctor(doctor,name);

    if(searchDoctor(doctor,name)){
        return *doctor;
    }else{
        cout<<"Doctor does not exist !\n\n";
        cout<<"There is the list of doctors Available is our Hospital :\n\n";
        printDoctor(doctor);
        //TakeAppointment();
        string drname;
        cout<<"Enter DR name :";
        cin>>drname;
        *doctor = FindDoctor(doctor,drname);
        TakeAppointment();
    }

}


void TakeAppointment(){
    int day;
    int month;
    int hour;
    int min;


    string drname;
    cout<<"Enter DR name :";
    cin>>drname;

    if( searchDoctor(doctor,drname)){
        *doctor = FindDoctor(doctor,drname);


        cout<<"Day :";
        cin>>day;

        cout<<"Month : ";
        cin>>month;

        cout<<"hour : ";
        cin>>hour;

        cout<<"minutes : ";
        cin>>min;
    }else
        *doctor = FindDoctor(doctor,drname);

    if(AppointmentExist(doctor,day,month,hour,min))
    {
        int p;
        cout<<"Sorry The Appointment is Already Taken - - - \n";
        cout<<"1-Take another appointment\n2-see Available appointments\n\n";
        cin>>p;

        if(p == 1){
            TakeAppointment();
        }else
        if(p == 2){
            Appointment appointment;
            appointment.AvailableAppointments();
        }


    }else{
        setAppointment(doctor,day,month,hour,min,drname);
    }

}

Doctor getDoctor(string name){
    if(searchDoctor(doctor,name)){
        return *doctor;
    }else{
        cout<<"Doctor does not exist !\n\n";
    }

}

void Appointment::AvailableAppointments(){

    cout<<"\n\n---------------------Available appointments -----------------------\n\n";

    cout<<"1. Dr Mona --> ";
    Appointment::appointmentToString(a,1,5,12,10);
    cout<<endl;

    cout<<"2. Dr William --> ";
    Appointment::appointmentToString(a,3,6,1,30);
    cout<<endl;
    cout<<"3. Dr Myles --> ";
    Appointment::appointmentToString(a,1,5,12,10);
    cout<<endl;

    cout<<"4. Dr Mark --> ";
    Appointment::appointmentToString(a,3,6,1,30);
    cout<<endl;
    int nb;


    char yes;
    do{
        cout<<"Would you like to Take an Appointment ?(y/n)"<<endl;
        cout<<">>";
        cin>>yes;
    }while(yes != 'y' && yes != 'n');

    if(yes == 'y'){


        cout<<"Enter Appointment nb : ";
        cin>>nb;

        switch(nb){
            case 1:
                *doctor = getDoctor("DrMona");

                doctor->appointment.day = 1;
                doctor->appointment.month = 5;
                doctor->appointment.hour = 12;
                doctor->appointment.min=10;
                break;

            case 2:
                *doctor = getDoctor("DrWilliam");

                doctor->appointment.day = 3;
                doctor->appointment.month = 6;
                doctor->appointment.hour = 1;
                doctor->appointment.min=30;
                break;

            case 3:
                *doctor = getDoctor("DrMyles");

                doctor->appointment.day = 1;
                doctor->appointment.month = 5;
                doctor->appointment.hour = 12;
                doctor->appointment.min=10;
                break;

            case 4:
                *doctor = getDoctor("DrMark");

                doctor->appointment.day = 3;
                doctor->appointment.month = 6;
                doctor->appointment.hour = 1;
                doctor->appointment.min=30;
                break;
        }


        cout<<"Appointment set Succefully !"<<endl;
    }



}



void searchDoctorSpecialization(Doctor *doctor,string specialization ){
    Doctor *cur = doctor;

    cout<<"List of "<<specialization<<" Doctor :"<<endl;;
    cout<<"Name\t\tLast Name \t\tSpecialization \t\tAvailable"<<endl;
    while(cur != NULL){
        if((cur->specialization).compare(specialization) == 0){

            int day = cur->appointment.day;
            string sday;
            switch (day) {
                case 1:
                    sday ="Monday";
                    break;
                case 2:
                    sday ="Tuesday";
                    break;
                case 3:
                    sday ="Wednesday";
                    break;
                case 4:
                    sday ="Thursday";
                    break;
                case 5:
                    sday="Friday";
                    break;

                case 6:
                    sday ="Saturday";
                    break;

                case 7:
                    sday="Sunday";
                    break;

                default:
                    sday = "Monday";

            }
            cout<<cur->fname<<"\t\t"<<cur->lname<<"\t\t\t"<<cur->specialization<<"\t\t"<<sday<<endl;

        }

        cur = cur->next;
    }

}


void searchDoctorByName(Doctor *doctor,string name ){
    Doctor *cur = doctor;
    searchDoctor(doctor,name);

    if(searchDoctor(doctor,name)){

        cout<<"Name\t\tLast Name\t\tAge \t\tSpecialization"<<endl;
        while(cur != NULL){
            if((cur->fname).compare(name) == 0){
                cout<<cur->fname<<"\t\t"<<cur->lname<<"\t\t\t"<<cur->age<<"\t\t\t"<<cur->specialization<<"\t\t"<<endl;
            }

            cur = cur->next;
        }
    }
    else{
        cout<<"Doctor Do not Exist\nThis is The List of Available Doctors in our Hospital"<<endl;
        printDoctor(doctor);
    }


}



void InitializeRadiology(Radiology *rad){
    rad->radnb = 0;
}

bool RadiologyisFull (Radiology *rad)
{
    return (rad->radnb == MAXRAD);
}
bool RadiologyisEmpty (Radiology *rad)
{
    return (rad->radnb==0);
}


void readRadiologyData(Radiology *rad, string fname, string lname,int expyear, int roomnb,int patientnb,string type){
    static int i = 0;
    (rad+i)->fname = fname;
    (rad+i)->lname = lname;
    (rad+i)->expyear = expyear;
    (rad+i)->room_nb = roomnb;
    (rad+i)->patient_nb = patientnb;
    (rad+i)->type = type;
    i++;
    rad->radnb++;
}

void printRad(Radiology *rad){

    cout<<"First Name\t\tLast Name\t\tYears of Experience"<<endl;
    for(int i = 0; i < rad->radnb; i++){
        cout<<(rad+i)->fname<<"\t\t\t"<<(rad+i)->lname<<"\t\t\t"<<(rad+i)->expyear;
        cout<<"\t\tRoom :A"<<(rad+i)->room_nb<<"\t\t"<<(rad+i)->type;
        cout<<endl;
    }
}


Radiology *searchRadiologist(Radiology *rad, string name){
    for(int i =0; i< rad->radnb; i++){
        if(((rad+i)->fname).compare(name) == 0){
            return &rad[i];
        }
    }
    return nullptr;
}



void BookRadiologyScan(Radiology *rad){
    string name;
    string type;
    cout<<"\n...booking Radiology scan\n";

    cout<<"Enter Name of Radiologist :";
    cin>>name;

    searchRadiologist(rad,name);
    if(searchRadiologist(rad,name) == nullptr){
        cout<<"Radiologist not Available \n";
        cout<<"Your Appointment will be booked with Dr.Mark\n\n";
        name = "Mark";
    }

    do{
        cout<<"Enter type of Scan (MRI - CT - PET):";
        cin>>type;
    }while(type.compare("CT") != 0 && type.compare("PET") != 0 &&type.compare("MRI") != 0 );

    int room = rand()%6+ 1;
    cout<<"\nloading...\n\n";
    cout<<"Your Radiology Appointment :\n";
    cout<<"With Dr."<<name<<"\tType of scan : "<<type<<"\tRoom : A"<<room<<endl;

    rad->patient_nb++;


}


void swap(Radiology *rad1, Radiology *rad2){
    Radiology temp;
    temp = *rad1;
    *rad1 = *rad2;
    *rad2 = temp;


}

void SortByYearofExperience(Radiology *rad){

    for(int i = 1; i <= rad->radnb-1 ; i++){
        for(int j = 0; j < rad->radnb - i; j++){
            if(rad[j].expyear > rad[j+1].expyear){
                swap(rad+j, rad+j+ 1);
            }
        }
    }

    cout<<"\n\nSorted Radiologits-------------\n\n";

    printRad(rad);
}


void MedicalHistory(Patient *patient){
    string pname;
    string al, altype, md, desc;
    bool found = false;

    cout<<"Enter Patient Name : ";
    cin>>pname;
    Patient *cur = patient;
    while(cur != NULL){
        if((cur->fullName).compare(pname) == 0 ){
            found = true;

            cout<<"Do The patient Have any Allegrie ?(yes/no) : ";
            cin>>al;
            if(al.compare("yes")==0){
                patient->MH.allergie = true;
                cout<<"Precise Allegie Type(Food Allergy - Pet Allergy - Medication Allergy) :\n";
                cin>>altype;
            }else{
                patient->MH.allergie = false;
            }

            cout<<"Do The patient Take any Medications ?(yes/no) :";
            cin>>md;
            if(md.compare("yes")==0){
                patient->MH.medication = true;
            }else{
                patient->MH.medication = false;
            }

            cout<<"Add Description : ";
            cin>>desc;

        }

        cur = cur->next;
    }

    if(found = false)
        cout<<"You Don't Have A Patient with this Name  !\n";

}

void Appointment::SpecificDoctorAppointment(){
    cout<<"Your Schedule---------------\n";

    int day = doctor->appointment.day;
    string sday;

    int month = doctor->appointment.month;
    string smonth;

    switch (day) {
        case 1:
            sday ="Monday";
            break;
        case 2:
            sday ="Tuesday";
            break;
        case 3:
            sday ="Wednesday";
            break;
        case 4:
            sday ="Thursday";
            break;
        case 5:
            sday="Friday";
            break;

        case 6:
            sday ="Saturday";
            break;

        case 7:
            sday="Sunday";
            break;

    }



    switch(month){
        case 1:
            smonth="January";
            break;

        case 2:
            smonth="February";
            break;

        case 3:
            smonth="March";
            break;

        case 4:
            smonth="April";
            break;

        case 5:
            smonth="May";
            break;

        case 6:
            smonth="June";
            break;

        case 7:
            smonth="July";
            break;

        case 8:
            smonth="August";
            break;
        case 9:
            smonth="September";
            break;
        case 10:
            smonth="October";
            break;
        case 11:
            smonth="November";
            break;
        case 12:
            smonth="December";
            break;
    }
    int year = 2022;

    string am;
    if(1< doctor->appointment.hour < 7){
        am ="PM";
    }
    else{
        am = "AM";
    }

    cout<<"Appointment : On "<<sday<<" in "<<smonth<<"\tAt: "<<doctor->appointment.hour<<":"<<doctor->appointment.min<<am<<endl;

}


void PatientBloodType(Patient *patient,string bloodtype ){
    cout<<"\n-----List of Patients with "<<bloodtype<<" Blood Type---------\n\n";
    Patient *cur = patient;
    cout<<"Name\t\tInsurance Number\t\tID\t\tBlood Type"<<endl;
    while(cur != NULL){
        if((cur->bloodType).compare(bloodtype) == 0 ){
            cout<<cur->fullName<<"\t\t"<<cur->ins_nb<<"\t\t\t"<<cur->id<<"\t\t"<<cur->bloodType<<endl;


        }

        cur = cur->next;
    }


}

void DeleteAppointment(Doctor *doctor,int month){
    Doctor *cur, *prev;

    if(doctor == NULL){
        cout<<"List Already Empty !!"<<endl;
    }


    if(doctor->appointment.month==month){
        cur=doctor->next;
        delete doctor;
        doctor=cur;

    }
    cur=doctor;
    prev=NULL;
    while(cur!=NULL && cur->appointment.month!=month){
        prev=cur;
        cur=cur->next;
    }

    if(cur==NULL)


        delete cur;

    cout<<"\nAppointment deleted succefully!\n\n";

}



