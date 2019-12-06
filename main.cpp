#include <iostream>
#include<bits/stdc++.h>
#include<string>
#include<fstream>
#include<windows.h>
#include<graphics.h>
#include<stdlib.h>
using namespace std;

COORD coord={0,0};

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int c=0;
void img()
{
    if(c==0)
    {
        initwindow(885,500,"MAP");
        readimagefile("mini_map.jpg",0,0,885,500);
    }
    c++;
}

class Patient
{
    string name;
    int age;


public:
    string bloodType;
    string location;
    void getPatient()
    //this function will take details and save it to a file
    // for further future use(for notifying when available).
    {
        img();
        gotoxy(8,3);
        cout<<"ENTER THE DETAILS OF PATIENT AND LOCATION";
        gotoxy(10,5);
        cout<<"Name\t\t\t\t: ";
        gotoxy(10,6);
        cout<<"Age\t\t\t\t: ";
        gotoxy(10,7);
        cout<<"Blood Type\t\t\t: ";
        gotoxy(10,8);
        cout<<"Enter location\t\t: ";
        gotoxy(45,5);
        fflush(stdin);
        getline(cin,name);
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        gotoxy(45,6);
        cin>>age;
        gotoxy(45,7);
        fflush(stdin);
        getline(cin, bloodType);
        gotoxy(45,8);
        fflush(stdin);
        getline(cin,location);
        transform(location.begin(), location.end(), location.begin(), ::toupper);
    }
};

//this function is used to store the list of location in an array to make easier to find in next steps.
void outVertex(ifstream& vertex, string locations[])
{
    int i=0;
    string loc;
    while(!vertex.eof())
    {
        while( getline(vertex, loc))
           {
               i++;
               locations[i]=loc;
           }
    }

}
void DetailsToFile(ofstream& file, string LOCATION, string NAME, string BTYPE, string ORGANISATION, string PHONE)
{
    gotoxy(5,3);
    cout<<"SUBMIT DETAILS OF DONORS: ";
    gotoxy(8,5);
    cout<<"Location \t\t: ";
    fflush(stdin);


    gotoxy(8,6);
    cout<< "Name \t\t\t: ";

    gotoxy(8,7);
    cout<< "Blood Type \t\t: ";

    gotoxy(8,8);
    cout<< "Phone no. \t\t: ";


    gotoxy(8,9);
    cout<<"Name of Organisation \t: ";


    gotoxy(36,5);
    getline(cin, LOCATION);
    transform(LOCATION.begin(), LOCATION.end(), LOCATION.begin(), ::toupper);

    gotoxy(36,6);
    fflush(stdin);// used to flush out the previous characters stored during compilation.
    getline(cin, NAME);
    transform(NAME.begin(), NAME.end(), NAME.begin(), ::toupper); //converts all string to upper case letters.

    gotoxy(36,7);
    fflush(stdin);
    getline(cin, BTYPE);
    transform(BTYPE.begin(), BTYPE.end(), BTYPE.begin(), ::toupper);

    gotoxy(36,8);
    fflush(stdin);
    getline(cin, PHONE);

    gotoxy(36,9);
    fflush(stdin);
    getline(cin, ORGANISATION);
    transform(ORGANISATION.begin(), ORGANISATION.end(), ORGANISATION.begin(), ::toupper);



        cout<<endl;
        string locations[19];

    //we stored all the locations in an array for future traversal use it will be easier.
        ifstream vertexOut;
        vertexOut.open("Location(vertex) List.txt");
        outVertex(vertexOut, locations);
        vertexOut.close();
        string loca=LOCATION;
        int x=0;
        transform(loca.begin(), loca.end(), loca.begin(), ::toupper);
        for(int i=1;i<=19;i++)
        {
            if(loca.compare(locations[i])==0)
            {
             x=i;
             break;
            }
        }


        if(x==0)
        {
        cout<<"SORRY YOU HAVE ENTERED A WRONG LOCATION (check spelling)"<<endl;
        }
        string bg=BTYPE;

        string bloodgrp[9]={"","O+","O-","A+","A-","B+","B-","AB+","AB-"};
        int bg1;int f2=0;



        for(int i=1;i<9;i++)
        {
        if(bg==bloodgrp[i])
        {
            bg1=i;
            f2=1;
        }
        }
        if(f2==0)
            cout<<"Invalid Blood Group"<<endl;

        file<<x<<" ";
        file<<bg1<<" ";
        file << LOCATION<< "\t";

        file << NAME<< "\t";
        file << BTYPE<< "\t";

        file << PHONE<< "\t";
        file << ORGANISATION<< "\t";
        file << endl;



    char op;
    cout<< "\tWant to enter more donors (Y/N) ??? : "; cin>>op;
    if(op=='Y'||op=='y')
    {
        system("CLS");
        DetailsToFile(file, LOCATION, NAME, BTYPE, ORGANISATION, PHONE);
    }
    else
        return;

}



struct locationNode{
    int index;
    float distWeight;
    float timeWeight;
    locationNode *left;
    locationNode *right;
};
struct locationNode *newNode(int index, float distWeight, float timeWeight)
{
    locationNode *temp=new locationNode;
    temp->index=index;
    temp->distWeight=distWeight;
    temp->timeWeight=timeWeight;
    temp->left=temp->right=NULL;
    return temp;
};
struct locationNode* insertToBST(struct locationNode* E, int index, float distWeight, float timeWeight)
{


    if(E==NULL)
    {
        E = newNode(index, distWeight, timeWeight);

        return E;
    }
    else if(distWeight>E->distWeight)
    {
        E->right = insertToBST(E->right, index, distWeight, timeWeight);
    }
    else
    {
        E->left = insertToBST(E->left, index, distWeight, timeWeight);
    }
    return E;
}

struct locationNode* insertToOURDATA(struct locationNode* E, int index, float distWeight, float timeWeight)
{


    if(E==NULL)
    {
        E = newNode(index, distWeight, timeWeight);
        return E;
    }
    else if(index>E->index)
    {

        E->right = insertToOURDATA(E->right, index, distWeight, timeWeight);

    }
    //we compared that if one index repeats then what is the possible shortest route or distance to that location.
    else if(index==E->index)
    {

        if(E->distWeight>distWeight)
        {
            E->distWeight=distWeight;
        }
        return E;
    }
    else if(index<E->index)
    {
        E->left = insertToOURDATA(E->left, index, distWeight,timeWeight);
    }
    return E;
}

int flag=0;
void getdata(int loc,string bg)
{
    transform(bg.begin(), bg.end(), bg.begin(), ::toupper);
    string bloodgrp[9]={"","O+","O-","A+","A-","B+","B-","AB+","AB-"};
    int loc1,bg1;int f1=0,f2=0;

    loc1=loc;

    for(int i=1;i<9;i++)
    {
        if(bg==bloodgrp[i])
        {
            bg1=i;
            f2=1;
        }
    }
        if(f2==0)
            cout<<"Invalid Blood Group"<<endl;
    ifstream fin;
    fin.open("DONOR DETAILS.txt");
    string line,word;
    int i;char x;
    while(fin)
    {
        fin>>i;
        if(i==loc1)
        {

            fin>>i;
           // cout<<i;
            if(i==bg1)
            {
               // cout<<i<<endl;
                fflush(stdin);
                getline(fin,line);
                fflush(stdin);
                flag=1;

                cout<<line<<endl;
            }
            else
            {
                fflush(stdin);
                getline(fin,line);
                fflush(stdin);

            }
        }
        else
        {

            fflush(stdin);
            getline(fin,line);
            fflush(stdin);
        }
    }//end of while

    fin.close();

}
void printOURDONORDETAILS(struct locationNode* E, string bg, int x)
{
    if(E!=NULL)
    {
        printOURDONORDETAILS(E->left, bg, x);
        getdata(E->index, bg);
        printOURDONORDETAILS(E->right, bg, x);

    }

}



int main()
{


    Patient p;
    char y='y';
    while(y=='y'||y=='Y')
    {
    system("cls");
    gotoxy(20,3);
    cout<<"BLOOD DONATION CAMP";
    gotoxy(25,5);
    cout<<"WELCOME!!!";
    gotoxy(16,8);
    cout<<"1. WANT TO BECOME A DONOR ? ";
    gotoxy(16,9);
    cout<<"2. WANT TO FIND BLOOD ? ";
    gotoxy(13,12);
    cout<<"ENTER YOUR CHOICE : ";
    int choice;
    gotoxy(34,12);
    cin>>choice;
    if(choice==1)
    {
        system("cls");
        ofstream file;
        file.open("DONOR DETAILS.txt", ios::app);
        string NAME, LOCATION, BTYPE, ORGANISATION, PHONE;
        DetailsToFile(file, LOCATION, NAME, BTYPE, ORGANISATION, PHONE);
        file.close();
    }
    else if(choice==2)
    {
        system("cls");
        float range;
        gotoxy(20,5);
        p.getPatient();
        cout<<"\n\tENTER RANGE(in KM) WITHIN WHICH WE WILL SEARCH THE DONORS : ";
        cin>>range;

        locationNode* Edge[19];

    for(int i=0;i<19;i++)
    {
        Edge[i]=new locationNode;
        Edge[i]=NULL;

    }


    Edge[1]=insertToBST(Edge[1], 2, 9.7);
    Edge[1]=insertToBST(Edge[1], 5, 10);
    Edge[1]=insertToBST(Edge[1], 6, 8.6);
    Edge[1]=insertToBST(Edge[1], 8, 2.9);
    Edge[1]=insertToBST(Edge[1], 7, 3.8);
    Edge[1]=insertToBST(Edge[1], 9, 11);
    Edge[1]=insertToBST(Edge[1], 13, 6.2);
    Edge[1]=insertToBST(Edge[1], 16, 12);
    Edge[1]=insertToBST(Edge[1], 1, 0.00);



    Edge[2]=insertToBST(Edge[2], 1, 9.7);
    Edge[2]=insertToBST(Edge[2], 3, 7.1);
    Edge[2]=insertToBST(Edge[2], 4, 3.4);
    Edge[2]=insertToBST(Edge[2], 5, 2.8);
    Edge[2]=insertToBST(Edge[2], 2, 0.00);



    Edge[3]=insertToBST(Edge[3], 2, 7.1);
    Edge[3]=insertToBST(Edge[3], 4, 4.5);
    Edge[3]=insertToBST(Edge[3], 17, 7.1);
    Edge[3]=insertToBST(Edge[3], 3, 0.00);



    Edge[4]=insertToBST(Edge[4], 2, 3.4);
    Edge[4]=insertToBST(Edge[4], 3, 4.5);
    Edge[4]=insertToBST(Edge[4], 4, 0.00);



    Edge[5]=insertToBST(Edge[5], 1, 10);
    Edge[5]=insertToBST(Edge[5], 2, 2.8);
    Edge[5]=insertToBST(Edge[5], 17, 4);
    Edge[5]=insertToBST(Edge[5], 6, 6.1);
    Edge[5]=insertToBST(Edge[5], 5, 0.00);



    Edge[6]=insertToBST(Edge[6], 1, 8.6);
    Edge[6]=insertToBST(Edge[6], 5, 6.1);
    Edge[6]=insertToBST(Edge[6], 18, 4.2);
    Edge[6]=insertToBST(Edge[6], 6, 0.00);



    Edge[7]=insertToBST(Edge[7], 1, 3.8);
    Edge[7]=insertToBST(Edge[7], 8, 5.3);
    Edge[7]=insertToBST(Edge[7], 9, 7.6);
    Edge[7]=insertToBST(Edge[7], 7, 0.00);



    Edge[8]=insertToBST(Edge[8], 1, 2.9);
    Edge[8]=insertToBST(Edge[8], 7, 5.3);
    Edge[8]=insertToBST(Edge[8], 8, 0.00);



    Edge[9]=insertToBST(Edge[9], 1, 11);
    Edge[9]=insertToBST(Edge[9], 7, 7.6);
    Edge[9]=insertToBST(Edge[9], 10, 6.4);
    Edge[9]=insertToBST(Edge[9], 9, 0.00);



    Edge[10]=insertToBST(Edge[10], 9, 6.4);
    Edge[10]=insertToBST(Edge[10], 13, 7.5);
    Edge[10]=insertToBST(Edge[10], 11, 2.1);
    Edge[10]=insertToBST(Edge[10], 10, 0.00);



    Edge[11]=insertToBST(Edge[11], 10, 2.1);
    Edge[11]=insertToBST(Edge[11], 12, 7);
    Edge[11]=insertToBST(Edge[11], 11, 0.00);



    Edge[12]=insertToBST(Edge[12], 11, 7);
    Edge[12]=insertToBST(Edge[12], 14, 6.4);
    Edge[12]=insertToBST(Edge[12], 12, 0.00);



    Edge[13]=insertToBST(Edge[13], 10, 7.5);
    Edge[13]=insertToBST(Edge[13], 1, 6.2);
    Edge[13]=insertToBST(Edge[13], 13, 0.00);



    Edge[14]=insertToBST(Edge[14], 12, 6.4);
    Edge[14]=insertToBST(Edge[14], 15, 6.3);
    Edge[14]=insertToBST(Edge[14], 14, 0.00);



    Edge[15]=insertToBST(Edge[15], 14, 6.3);
    Edge[15]=insertToBST(Edge[15], 15, 0.00);


    Edge[16]=insertToBST(Edge[16], 16, 0.00);
    Edge[16]=insertToBST(Edge[16], 1, 12);


    Edge[17]=insertToBST(Edge[17], 17, 0.00);
    Edge[17]=insertToBST(Edge[17], 3, 7.1);
    Edge[17]=insertToBST(Edge[17], 5, 4);


    Edge[18]=insertToBST(Edge[18], 18, 0.00);
    Edge[18]=insertToBST(Edge[18], 6, 4.2);

    string locations[19];

    //we stored all the locations in an array for future traversal use it will be easier.
    ifstream vertexOut;
    vertexOut.open("Location(vertex) List.txt");
    outVertex(vertexOut, locations);
    vertexOut.close();

    string loca=p.location;
    int x=0;
    transform(loca.begin(), loca.end(), loca.begin(), ::toupper);
    for(int i=1;i<=19;i++)
    {
        if(loca.compare(locations[i])==0)
         {
             x=i;
             break;
         }
    }
    if(x==0)
    {
        cout<<"SORRY YOU HAVE ENTERED A WRONG LOCATION"<<endl;
    }
    else
    {
            traversalOfEdge(Edge[x], range, Edge, x, 0);
            printOURDONORDETAILS(Edge[0], p.bloodType, x);
    }
    if(flag==0)
    {
        cout<<"\t\tSORRY NO ANY DONOR FOUND OF THAT BLOOD GROUP !!!"<<endl;
    }


    }
    else
        cout<<"\n\tPLEASE Enter a VALID CHOICE !!!"<<endl;

    cout<<"\n \t\tWant to continue (y/n) : ";
    cin>>y;
    }
    return 0;
}

