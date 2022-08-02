#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "rapidcsv.h"
#include <Windows.h>
using namespace std;
using namespace rapidcsv;

void SetColor (int background_color, int text_color)
{
    HANDLE hStdout = GetStdHandle (STD_OUTPUT_HANDLE);
    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
// Data of Nhan Vien
struct NhanVien
{
    string Name_NV, QR_NV, Gender, Phone;
    int Age;
};
typedef struct NhanVien NHANVIEN;
//-------------------------------------------
//Data of San Pham
struct Product
{
    string Name_Product, ID_Product, Categorize;
    float Sold_price, Price;
    int Quantity, Initial_quantity, Sold_quantity, Inventory_quantity;
};
typedef struct Product PRODUCT;
//-------------------------------------------
//Data of Khach Hang
struct Custom
{
    string Name_Custom, ID_Custom, Phone;
    float Point;
};
typedef struct Custom CUSTOM;
//-------------------------------------------
//BILL 
struct Bill
{
    int Quantity;
    string Day, Month, Year, ID_Customer, ID_Product, Name_Product, Name_Customer, Date;
    float Amount, Price;
};
typedef struct Bill BILL;
//-------------------------------------------
// Pointer of Nhan Vien
struct Node_Nv
{
    NHANVIEN* NV;
    Node_Nv* pnext;
};
typedef struct Node_Nv NODE_NV;
//-------------------------------------------
// Pointer of San Pham
struct Node_Sp
{
    PRODUCT* SP;
    Node_Sp* pnext;
};
typedef struct Node_Sp NODE_SP;
//-------------------------------------------
// Pointer of Khach Hang
struct Node_Kh
{
    CUSTOM* CUS;
    Node_Kh* pnext;
};
typedef struct Node_Kh NODE_KH;
//-------------------------------------------
// Pointer of Hoa Don
struct Node_Bill
{
    BILL *Bill;
    Node_Bill* pnext;
};
typedef struct Node_Bill NODE_BILL;
struct List
{
    NODE_NV* pHead_nv;
    //NODE_NV *pTail_nv;
    NODE_SP* pHead_sp;
    //NODE_SP *pTail_sp;
    NODE_KH* pHead_kh;
    //NODE_KH *pTail_kh;  
    NODE_BILL* pHead_bill;
    //NODE_KH *pTail_bill;      
};
typedef struct List LIST;
Document readFileCSV(const string &fileName) 
{
    Document document;
    try {
        document.Load("../ADS_Final_Project/" + fileName);
    } catch (ifstream::failure const &ex) {
        cout << ex.what() << ": No such file or directory";
        system("exit");
    }
    return document;
}
void Initialize(LIST& list)
{
    list.pHead_nv = NULL;
    list.pHead_sp = NULL;
    list.pHead_kh = NULL;
    list.pHead_bill = NULL;
}
NODE_NV* Information_Staff()
{
    SetColor(0, 11);
    NHANVIEN* NV = new NHANVIEN;
    cout << "\t\t\t\t\tENTER QR OF STAFF: " << endl;
    cout << "\t\t\t\t\t";
    cin >> NV->QR_NV;
    cout << "\t\t\t\t\tENTER NAME OF STAFF: " << endl;
    cout << "\t\t\t\t\t";
    cin >> NV->Name_NV;
    cout << "\t\t\t\t\tENTER AGE OF STAFF: " << endl;
    cout << "\t\t\t\t\t";
    cin >> NV->Age;
    cout << "\t\t\t\t\tENTER GENDER OF STAFF: " << endl;
    cout << "\t\t\t\t\t";
    cin >> NV->Gender;
    cout << "\t\t\t\t\tENTER PHONE OF STAFF: " << endl;
    cout << "\t\t\t\t\t";
    cin >> NV->Phone;

    NODE_NV* node = new NODE_NV;
    node->NV = NV;
    node->pnext = NULL;
    return node;
}
NODE_SP* Information_Product()
{
    SetColor(0, 11);
    PRODUCT* PROD = new PRODUCT;
    cout << "\t\t\t\t\tENTER NAME OF PRODUCT: " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->Name_Product;
    cout << "\t\t\t\t\tENTER ID PRODUCT: " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->ID_Product;
    cout << "\t\t\t\t\tENTER CATEGORIZE : " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->Categorize;
    cout << "\t\t\t\t\tENTER PRICE : " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->Price;
    cout << "\t\t\t\t\tENTER BONUS PRICE : " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->Sold_price;
    cout << "\t\t\t\t\tENTER INITIAL QUANTITY : " << endl;
    cout << "\t\t\t\t\t";
    cin >> PROD->Initial_quantity;
    PROD->Quantity = PROD->Initial_quantity;
    NODE_SP* node = new NODE_SP;
    node->SP = PROD;
    node->pnext = NULL;
    return node;
}
NODE_KH* Information_Custom()
{
    SetColor(0, 11);
    CUSTOM* CUS = new CUSTOM;
    cout << "\t\t\t\t\tENTER NAME OF CUSTOM : " << endl;
    cout << "\t\t\t\t\t";
    cin >> CUS->Name_Custom;
    cout << "\t\t\t\t\tENTER QR OF CUSTOM : " << endl;
    cout << "\t\t\t\t\t";
    cin >> CUS->ID_Custom;
    cout << "\t\t\t\t\tENTER PHONE OF CUSTOM : " << endl;
    cout << "\t\t\t\t\t";
    cin >> CUS->Phone;
    CUS->Point = 0;
    NODE_KH* node = new NODE_KH;
    node->CUS = CUS;
    node->pnext = NULL;
    return node;
}
NODE_BILL* Bill()
{
    SetColor(0, 11);
    BILL* Bill = new BILL;
    cout << "\t\t\t\t\tENTER DAY MONTH YEAR(SPACE) : ";
    cin >> Bill->Day;
    cin >> Bill->Month;
    cin >> Bill->Year;
    Bill->Date = Bill->Day + "/" + Bill->Month + "/" + Bill->Year;
    NODE_BILL* node = new NODE_BILL;
    node->Bill = Bill;
    node->pnext = NULL;
    return node;
}
NODE_NV* Read_NV(size_t j)
{
        NHANVIEN* NV = new NHANVIEN;
        Document doc = readFileCSV("STAFF.csv");
        NV->QR_NV = doc.GetCell<string>("QR",j);
        NV->Name_NV = doc.GetCell<string>("NAME",j);
        NV->Age = doc.GetCell<int>("AGE",j);
        NV->Gender = doc.GetCell<string>("GENDER",j);
        NV->Phone = doc.GetCell<string>("PHONE",j);
        NODE_NV* node = new NODE_NV;
        node->NV = NV;
        node->pnext = NULL;
        return node;
}
NODE_SP* Read_SP(size_t i)
{
        PRODUCT* PROD = new PRODUCT;
        Document doc = readFileCSV("SANPHAM.csv");
        PROD->Name_Product = doc.GetCell<string>("NAME",i);
        PROD->ID_Product = doc.GetCell<string>("ID",i);
        PROD->Categorize = doc.GetCell<string>("CATEGORIZE",i);
        PROD->Price = doc.GetCell<float>("PRICE",i);
        PROD->Sold_price = doc.GetCell<float>("SOLD PRICE",i);
        PROD->Initial_quantity = doc.GetCell<int>("QUANTITY",i);
        PROD->Quantity = doc.GetCell<int>("QUANTITY",i);
        NODE_SP* node = new NODE_SP;
        node->SP = PROD;
        node->pnext = NULL;
        return node;
}
NODE_KH* Read_KH(size_t k)
{
        CUSTOM* CUS = new CUSTOM;
        Document doc = readFileCSV("CUSTOMER.csv");
        CUS->Name_Custom = doc.GetCell<string>("NAME",k);
        CUS->ID_Custom = doc.GetCell<string>("ID",k);
        CUS->Phone = doc.GetCell<string>("PHONE",k);
        CUS->Point = doc.GetCell<float>("POINT",k);
        NODE_KH* node = new NODE_KH;
        node->CUS = CUS;
        node->pnext = NULL;
        return node;
}
NODE_BILL* Read_TK(size_t e)
{
        BILL* BIL = new BILL;
        Document doc = readFileCSV("STATISTIC.csv");
        BIL->Date = doc.GetCell<string>("DATE",e);
        BIL->ID_Customer= doc.GetCell<string>("ID_KH",e);
        BIL->Name_Customer = doc.GetCell<string>("NAME_KH",e);
        BIL->ID_Product = doc.GetCell<string>("ID_SP",e);
        BIL->Name_Product = doc.GetCell<string>("NAME_SP",e);
        BIL->Quantity = doc.GetCell<int>("QUANTITY",e);
        BIL->Price = doc.GetCell<float>("PRICE",e);
        BIL->Amount = BIL->Quantity*BIL->Price;
        NODE_BILL* node = new NODE_BILL;
        node->Bill = BIL;
        node->pnext = NULL;
        return node;
}
void Load_csv(LIST& lst, int id)
{
    Document Read_sp = readFileCSV("SANPHAM.csv");
    Document Read_nv = readFileCSV("STAFF.csv");
    Document Read_kh = readFileCSV("CUSTOMER.csv");
    Document Read_tk = readFileCSV("STATISTIC.csv");
    size_t count_sp = Read_sp.GetRowCount();
    size_t count_nv = Read_nv.GetRowCount();
    size_t count_kh = Read_kh.GetRowCount();
    size_t count_tk = Read_tk.GetRowCount();
    if(lst.pHead_nv == NULL && id == 0)
    {
        for( size_t j = 0; j < count_nv; j++)
        {
            NODE_NV *node_nv = Read_NV(j);
            if (lst.pHead_nv == NULL)
            {
                lst.pHead_nv = node_nv;
            }
            else
            {
                node_nv->pnext = lst.pHead_nv;
                lst.pHead_nv = node_nv;
            }
        }
    }
    else
    if(lst.pHead_sp == NULL && id == 1)
    {
        for( size_t i = 0; i < count_sp; i++)
        {
            NODE_SP *node_sp = Read_SP(i);
            if (lst.pHead_sp == NULL)
            {
                lst.pHead_sp = node_sp;
            }
            else
            {
                node_sp->pnext = lst.pHead_sp;
                lst.pHead_sp = node_sp;
            }
        }
    }
    else
    if(lst.pHead_kh == NULL && id == 2)
    {
        for(size_t k = 0; k < count_kh; k++)
        {
            NODE_KH *node_kh = Read_KH(k);
            if (lst.pHead_kh == NULL)
            {
                lst.pHead_kh = node_kh;
            }
            else
            {
                node_kh->pnext = lst.pHead_kh;
                lst.pHead_kh = node_kh;
            }
        }
    }
    else
    if(lst.pHead_bill == NULL && id == 3)
    {
        for(size_t e = 0; e < count_tk; e++)
        {
            NODE_BILL *node_bill = Read_TK(e);
            if (lst.pHead_bill == NULL)
            {
                lst.pHead_bill = node_bill;
            }
            else
            {
                node_bill->pnext = lst.pHead_bill;
                lst.pHead_bill = node_bill;
            }
        }
    }
}
void InsertHead(LIST& lst, int id)
{
    if (id == 0) // Nhan Vien
    {
        NODE_NV* node_nv = Information_Staff();
        if (lst.pHead_nv == NULL)
        {
            lst.pHead_nv = node_nv;
        }
        else
        {
            node_nv->pnext = lst.pHead_nv;
            lst.pHead_nv = node_nv;
        }
    }
    else
    if (id == 1) // San Pham
    {
        NODE_SP* node_sp = Information_Product();
        if (lst.pHead_sp == NULL)
        {
            lst.pHead_sp = node_sp;
        }
        else
        {
            node_sp->pnext = lst.pHead_sp;
            lst.pHead_sp = node_sp;
        }
    }
    else
    if (id == 2) // Khach Hang
    {
        NODE_KH* node_kh = Information_Custom();
        if (lst.pHead_kh == NULL)
        {
            lst.pHead_kh = node_kh;
        }
        else
        {
            node_kh->pnext = lst.pHead_kh;
            lst.pHead_kh = node_kh;
        }
    }
    else
    if (id == 3) // BILL
        {
            NODE_BILL* node_bill = Bill();
            if (lst.pHead_bill == NULL)
            {
                lst.pHead_bill = node_bill;
            }
            else
            {
                node_bill->pnext = lst.pHead_bill;
                lst.pHead_bill = node_bill;
            }
            }        
}
void Print_NV(NHANVIEN* NV)
{
    SetColor(0,11);
    cout << NV->QR_NV;
    cout << setw(16 - NV->QR_NV.length()) << "|";
    cout << NV->Name_NV;
    cout << setw(16 - NV->Name_NV.length()) << "|";
    cout << NV->Age;
    cout << setw(10 - to_string(NV->Age).length()) << "|";
    cout << NV->Gender;
    cout << setw(14 - NV->Gender.length()) << "|";
    cout << NV->Phone;
    cout << setw(31 - NV->Phone.length()) << "|" << endl;
}
void Print_SP(PRODUCT* PROD)
{
    SetColor(0,11);
    cout << PROD->Name_Product;
    cout << setw(16 - PROD->Name_Product.length()) << "|";
    cout << PROD->ID_Product;
    cout << setw(16 - PROD->ID_Product.length()) << "|";
    cout << PROD->Categorize;
    cout << setw(16 - PROD->Categorize.length()) << "|";
    cout << PROD->Price;
    cout << setw(16 - to_string((int)PROD->Price).length()) << "|";
    cout << PROD->Sold_price;
    cout << setw(16 - to_string((int)PROD->Sold_price).length()) << "|";
    cout << PROD->Quantity;
    cout << setw(16 - to_string((int)PROD->Initial_quantity).length()) << "|" << endl;
}
void Print_KH(CUSTOM* CUS)
{
    SetColor(0,11);
    cout << CUS->Name_Custom;
    cout << setw(16 - CUS->Name_Custom.length()) << "|";
    cout << CUS->ID_Custom;
    cout << setw(16 - CUS->ID_Custom.length()) << "|";
    cout << CUS->Phone;
    cout << setw(16 - CUS->Phone.length()) << "|";
    cout << CUS->Point;
    cout << setw(16 - to_string((int)CUS->Point).length()) << "|" << endl;
}
void Print_BILL(BILL* Bill)
{
    SetColor(0,11);
    //cout << Bill->Day << "/" << Bill->Month << "/" << Bill->Year;
    cout << Bill->Date;
    //cout << setw(16 - Bill->Day.length() - Bill->Month.length() - Bill->Year.length() - 2 ) << "|";
    cout << setw(16 - Bill->Date.length() ) << "|";
    cout << Bill->ID_Customer;
    cout << setw(16 - Bill->ID_Customer.length()) << "|";
    cout << Bill->Name_Customer;
    cout << setw(14 - Bill->Name_Customer.length()) << "|";
    cout << Bill->ID_Product;
    cout << setw(16 - Bill->ID_Product.length()) << "|";
    cout << Bill->Name_Product;
    cout << setw(14 - Bill->Name_Product.length()) << "|";
    cout << Bill->Quantity;
    cout << setw(16 - to_string((int)Bill->Quantity).length()) << "|";
    cout << Bill->Price;
    cout << setw(16 - to_string((int)Bill->Price).length()) << "|";
    cout << Bill->Amount;
    cout << setw(16 - to_string((int)Bill->Amount).length()) << "|" << endl;
}
void PrintList(LIST& lst, int id)
{
    if (id == 0) // STAFF
    {
        //Load_csv(lst,0);
        if (lst.pHead_nv != NULL)
        {
            NODE_NV* pnode_nv = lst.pHead_nv;
            string test;
            SetColor(0,11);
            cout << "\n\t\t-----------------LIST OF STAFF INFORMATION---------------- " << endl;
            cout << setw(10) << right << "QR";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "NAME";
            cout << setw(6) << right << "|";
            cout << setw(6) << right << "AGE";
            cout << setw(4) << right << "|";
            cout << setw(10) << right << "GENDER";
            cout << setw(4) << right << "|";
            cout << setw(18) << right << "PHONE";
            cout << setw(13) << right << "|" << endl;
            fstream of0;
            of0.open("STAFF.csv", ios_base::out);
            of0 << "QR,NAME,AGE,GENDER,PHONE" << endl;
            while (pnode_nv != NULL)
            {
                string test;
                test = pnode_nv->NV->QR_NV + "," + pnode_nv->NV->Name_NV + "," + to_string(pnode_nv->NV->Age) + "," + pnode_nv->NV->Gender + "," + pnode_nv->NV->Phone;
                Print_NV(pnode_nv->NV);
                pnode_nv = pnode_nv->pnext;
                of0 << test << endl;
            }
            of0.close();
        }
    }
    if (id == 1) // PRODUCT
    {
        //Load_csv(lst,1);
        if (lst.pHead_sp != NULL)
        {
            SetColor(0,11);
            NODE_SP* pnode_sp = lst.pHead_sp;
            cout << "\n\t\t-----------------LIST OF PRODUCT INFORMATION---------------- " << endl;
            cout << setw(10) << right << "NAME";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "ID";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "CATEGORIZE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "PRICE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "SOLD PRICE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "QUANTITY";
            cout << setw(6) << right << "|" << endl;
            fstream of1;
            of1.open("SANPHAM.csv", ios_base::out);
            of1 << "NAME,ID,CATEGORIZE,PRICE,SOLD PRICE,QUANTITY" << endl;
            while (pnode_sp != NULL)
            {
                string test1;
                test1 = pnode_sp->SP->Name_Product + "," + pnode_sp->SP->ID_Product + "," + pnode_sp->SP->Categorize + "," + to_string(pnode_sp->SP->Price)
                    + "," + to_string(pnode_sp->SP->Sold_price) + "," + to_string(pnode_sp->SP->Quantity);
                Print_SP(pnode_sp->SP);
                pnode_sp = pnode_sp->pnext;
                of1 << test1 << endl;
            }
            of1.close();
        }
    }
    if (id == 2) // CUSTOMER
    {
        //Load_csv(lst,2);
        if (lst.pHead_kh != NULL)
        {
            SetColor(0,11);
            NODE_KH* pnode_kh = lst.pHead_kh;
            cout << "\n\t\t-----------------LIST OF CUSTOMER INFORMATION---------------- " << endl;
            cout << setw(10) << right << "NAME";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "ID";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "PHONE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "POINT";
            cout << setw(6) << right << "|" << endl;
            fstream of2;
            of2.open("CUSTOMER.csv", std::ios_base::out);
            of2 << "NAME,ID,PHONE,POINT" << endl;
            while (pnode_kh != NULL)
            {
                string test2;
                test2 = pnode_kh->CUS->Name_Custom + "," + pnode_kh->CUS->ID_Custom + "," + pnode_kh->CUS->Phone + "," + to_string(pnode_kh->CUS->Point);
                Print_KH(pnode_kh->CUS);
                pnode_kh = pnode_kh->pnext;
                of2 << test2 << endl;
            }
            of2.close();
        }
    }
    if (id == 3) // BILL
    {
        if (lst.pHead_bill != NULL)
        {
            SetColor(0,11);
            NODE_BILL* pnode_bill = lst.pHead_bill;
            cout << "\n\t\t-----------------BILL---------------- " << endl;
            cout << setw(10) << right << "DATE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "ID_KH";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "NAME_KH";
            cout << setw(4) << right << "|";
            cout << setw(10) << right << "ID_SP";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "NAME_SP";
            cout << setw(4) << right << "|";
            cout << setw(10) << right << "QUANTITY";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "PRICE";
            cout << setw(6) << right << "|";
            cout << setw(10) << right << "AMOUNT";
            cout << setw(6) << right << "|" << endl;
            fstream of3;
            of3.open("STATISTIC.csv", std::ios_base::out);
            of3 << "DATE,ID_KH,NAME_KH,ID_SP,NAME_SP,QUANTITY,PRICE" << endl;
            while (pnode_bill != NULL)
            {
                string test3;
                test3 = pnode_bill->Bill->Date + "," + pnode_bill->Bill->ID_Customer + "," + pnode_bill->Bill->Name_Customer +"," 
                + pnode_bill->Bill->ID_Product + "," + pnode_bill->Bill->Name_Product + ","
                + to_string(pnode_bill->Bill->Quantity) + "," + to_string((int)pnode_bill->Bill->Price);
                Print_BILL(pnode_bill->Bill);
                of3 << test3 << endl;
                pnode_bill = pnode_bill->pnext;
            }
            of3.close();
        }
    }
}
bool Search_NV(NHANVIEN* NV, string id)
{
    if (NV->QR_NV == id)
        return true;
    else
        return false;
}
void CheckSearch_NV(bool check, NODE_NV* node)
{
    if (check == true && node == NULL)
    {
        cout << "\t\t\t\t\tSUCCESS FINDING" << endl;
    }
    if (check == false && node == NULL)
    {
        cout << "\t\t\t\t\tERROR, NOT FINDING" << endl;
    }
}
void PrintSearch_NV(LIST& lst, string id)
{
    bool check = false;
    CheckSearch_NV(check, lst.pHead_nv);
    if (lst.pHead_nv != NULL)
    {
        NODE_NV* node = lst.pHead_nv;
        while (node != NULL)
        {
            if (Search_NV(node->NV, id))
            {
                check = true;
                Print_NV(node->NV);
            }
            node = node->pnext;
            CheckSearch_NV(check, node);
        }

    }
}
bool Search_SP(PRODUCT* PROD, string id)
{
    if (PROD->ID_Product == id)
        return true;
    else
        return false;
}
void CheckSearch_SP(bool check, NODE_SP* node)
{
    if (check == true && node == NULL)
    {
        cout << "\t\t\t\t\tSUCCESS FINDING" << endl;
    }
    if (check == false && node == NULL)
    {
        cout << "\t\t\t\t\tERROR, NOT FINDING" << endl;
    }
}
void PrintSearch_SP(LIST& lst, string id)
{
    bool check = false;
    CheckSearch_SP(check, lst.pHead_sp);
    if (lst.pHead_sp != NULL)
    {
        NODE_SP* node = lst.pHead_sp;
        while (node != NULL)
        {
            if (Search_SP(node->SP, id))
            {
                check = true;
                Print_SP(node->SP);
            }
            node = node->pnext;
            CheckSearch_SP(check, node);
        }

    }
}
void Delete_SP(LIST& l, string Id_pro)
{
    NODE_SP* node_Del = l.pHead_sp;
    if (node_Del == NULL)
    {
        cout << "\t\t\t\t\tNO LIST";
    }
    else
    {
        NODE_SP* node_Pre = NULL;
        while (node_Del != NULL)
        {
            if (node_Del->SP->ID_Product == Id_pro)
                break;
            node_Pre = node_Del;
            node_Del = node_Del->pnext;
        }
        if (node_Del == NULL)
        {
            cout << "\t\t\t\t\tID Not Found " << Id_pro;
        }
        else
        {
            if (node_Del == l.pHead_sp)
            {
                l.pHead_sp = l.pHead_sp->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
            else
            {
                node_Pre->pnext = node_Del->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
        }
    }
}
void Delete_NV(LIST& l, string Id_NV)
{
    NODE_NV* node_Del = l.pHead_nv;
    if (node_Del == NULL)
    {
        cout << "\t\t\t\t\tNO LIST";
    }
    else
    {
        NODE_NV* node_Pre = NULL;
        while (node_Del != NULL)
        {
            if (node_Del->NV->QR_NV == Id_NV)
                break;
            node_Pre = node_Del;
            node_Del = node_Del->pnext;
        }
        if (node_Del == NULL)
        {
            cout << "\t\t\t\t\tID Not Found " << Id_NV;
        }
        else
        {
            if (node_Del == l.pHead_nv)
            {
                l.pHead_nv = l.pHead_nv->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
            else
            {
                node_Pre->pnext = node_Del->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
        }
    }
}
void Delete_KH(LIST& l, string Id_KH)
{
    NODE_KH* node_Del = l.pHead_kh;
    if (node_Del == NULL)
    {
        cout << "\t\t\t\t\tNO LIST";
    }
    else
    {
        NODE_KH* node_Pre = NULL;
        while (node_Del != NULL)
        {
            if (node_Del->CUS->ID_Custom == Id_KH)
                break;
            node_Pre = node_Del;
            node_Del = node_Del->pnext;
        }
        if (node_Del == NULL)
        {
            cout << "\t\t\t\t\tID Not Found " << Id_KH;
        }
        else
        {
            if (node_Del == l.pHead_kh)
            {
                l.pHead_kh = l.pHead_kh->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
            else
            {
                node_Pre->pnext = node_Del->pnext;
                node_Del->pnext = NULL;
                delete node_Del;
                node_Del = NULL;
            }
        }
    }
}
void Buy_SP(LIST& l, string input_qr, string id_custom, int k)
{
    NODE_SP* node_sp = l.pHead_sp;
    NODE_KH* node_kh = l.pHead_kh;
    NODE_BILL* node_bill = l.pHead_bill;
    // Update BILL
    node_bill->Bill->Quantity = k;
    while (node_sp != NULL)
    {
        if (node_sp->SP->ID_Product == input_qr)
        {
            node_bill->Bill->ID_Product = input_qr;
            node_bill->Bill->Name_Product = node_sp->SP->Name_Product;
            for (int i = 0; i < k; i++)
            {
                node_sp->SP->Quantity -= 1;
            }
            node_sp->SP->Sold_quantity = node_sp->SP->Initial_quantity - node_sp->SP->Quantity;
            if (node_sp->SP->Sold_price == 0) // NOT BONUS
            {
                node_bill->Bill->Amount = node_sp->SP->Sold_quantity*node_sp->SP->Price;
                node_bill->Bill->Price = node_sp->SP->Price;
            }
            else
            if (node_sp->SP->Sold_price != 0) // BONUS
            {
                node_bill->Bill->Amount = node_sp->SP->Sold_quantity*node_sp->SP->Sold_price;
                node_bill->Bill->Price = node_sp->SP->Sold_price;
                }
            while (node_kh != NULL)
            {
                if (node_kh->CUS->ID_Custom == id_custom)
                {
                    node_bill->Bill->ID_Customer = id_custom;
                    node_bill->Bill->Name_Customer = node_kh->CUS->Name_Custom;
                    if (node_sp->SP->Sold_price == 0) // NOT BONUS
                    {
                        node_kh->CUS->Point = node_sp->SP->Price * k * 0.01 / 100;
                    }
                    else
                    if (node_sp->SP->Sold_price != 0) // BONUS
                    {
                        node_kh->CUS->Point = node_sp->SP->Sold_price * k * 0.01 / 100;
                    }
                }
                node_kh = node_kh->pnext;
            }
        }
            node_sp->SP->Inventory_quantity = node_sp->SP->Quantity;
            node_sp = node_sp->pnext;
            //node_bill = node_bill->pnext;
        
    }
}
void Swap_SP(NODE_SP *Temp_i, NODE_SP *Temp_j)
{
    NODE_SP *tmp = new NODE_SP;
    tmp->SP = Temp_i->SP;
    Temp_i->SP = Temp_j->SP;
    Temp_j->SP = tmp->SP;
}
void Swap_KH(NODE_KH *Temp_i, NODE_KH *Temp_j)
{
    NODE_KH *tmp = new NODE_KH;
    tmp->CUS = Temp_i->CUS;
    Temp_i->CUS = Temp_j->CUS;
    Temp_j->CUS = tmp->CUS;
}
void Swap_NV(NODE_NV *Temp_i, NODE_NV *Temp_j)
{
    NODE_NV *tmp = new NODE_NV;
    tmp->NV = Temp_i->NV;
    Temp_i->NV = Temp_j->NV;
    Temp_j->NV = tmp->NV;
}
void SortList(LIST &l, string object,string types, bool sort)
{
    string ID_i, ID_j;
    if(types == "ID" && object == "PRODUCT")
    {
        for(NODE_SP *Temp_i = l.pHead_sp; Temp_i != NULL; Temp_i = Temp_i->pnext)
        {
            for(NODE_SP *Temp_j = Temp_i->pnext; Temp_j != NULL; Temp_j = Temp_j->pnext)
            {
                if (sort == 0) //Ascending
                {
                    std::string i(Temp_i->SP->ID_Product);
                    std::string j(Temp_j->SP->ID_Product);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i > ID_j)
                    {
                        Swap_SP(Temp_i,Temp_j);
                    }
                }
                else
                if (sort == 1) //Descending
                {
                    std::string i(Temp_i->SP->ID_Product);
                    std::string j(Temp_j->SP->ID_Product);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i < ID_j)
                    {
                        Swap_SP(Temp_i,Temp_j);
                    }
                }
            }
        }
    }
    if(types == "ID" && object == "STAFF")
    {
        for(NODE_NV *Temp_i = l.pHead_nv; Temp_i != NULL; Temp_i = Temp_i->pnext)
        {
            for(NODE_NV *Temp_j = Temp_i->pnext; Temp_j != NULL; Temp_j = Temp_j->pnext)
            {
                if (sort == 0) //Ascending
                {
                    std::string i(Temp_i->NV->QR_NV);
                    std::string j(Temp_j->NV->QR_NV);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i > ID_j)
                    {
                        Swap_NV(Temp_i,Temp_j);
                    }
                }
                else
                if (sort == 1) //Descending
                {
                    std::string i(Temp_i->NV->QR_NV);
                    std::string j(Temp_j->NV->QR_NV);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i < ID_j)
                    {
                        Swap_NV(Temp_i,Temp_j);
                    }
                }
            }
        }
    }
    if(types == "ID" && object == "CUSTOMER")
    {
        for(NODE_KH *Temp_i = l.pHead_kh; Temp_i != NULL; Temp_i = Temp_i->pnext)
        {
            for(NODE_KH *Temp_j = Temp_i->pnext; Temp_j != NULL; Temp_j = Temp_j->pnext)
            {
                if (sort == 0) //Ascending
                {
                    std::string i(Temp_i->CUS->ID_Custom);
                    std::string j(Temp_j->CUS->ID_Custom);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i > ID_j)
                    {
                        Swap_KH(Temp_i,Temp_j);
                    }
                }
                else
                if (sort == 1) //Descending
                {
                    std::string i(Temp_i->CUS->ID_Custom);
                    std::string j(Temp_j->CUS->ID_Custom);
                    ID_i = atoi(i.c_str());
                    ID_j = atoi(j.c_str());    
                    if(ID_i < ID_j)
                    {
                        Swap_KH(Temp_i,Temp_j);
                    }
                }
            }
        }
    }
}
void Export_Bill(LIST &l, string QR_customer, string Date)
{
    SetColor(0,15);
    NODE_BILL *node_bill = l.pHead_bill; 
    NODE_BILL *temp_bill = l.pHead_bill;
    int w = 70;
    float Total_amount = 0;
    bool check_date = false;
    cout << setw(20) << "";
    for(int i = 0; i<w;i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "\t\t\t\t\t\tWELCOME TO ADS SHOP " << endl;
    cout << "\t\t\t\t\t\t******************* \n";
    while(temp_bill != NULL)
    {
        if(temp_bill->Bill->Date == Date && temp_bill->Bill->ID_Customer == QR_customer) 
        {
            cout << setw(31) << "CUSTOMER : " << temp_bill->Bill->Name_Customer;
            cout << setw(42) << "DATE : " << Date << endl;
            check_date = true;
        break;
        }
        check_date = false;
        temp_bill = temp_bill->pnext;
    }
    if(!check_date)
    {
        cout << setw(31) << "CUSTOMER : " << "NA";
        cout << setw(42) << "DATE : " << "NA" << "/" << "NA" << "/" << "NA" << endl;
        Total_amount = 0;
    }
    cout << setw(20) << "";
    for(int i = 0; i<w;i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << setw(21) << "|";
    cout << setw(9) << "Name";
    cout << setw(20) << "Quantity";
    cout << setw(30) << "Price";
    cout << setw(10) << "|" << endl;
    while(node_bill != NULL)
    {
        if(node_bill->Bill->ID_Customer == QR_customer && node_bill->Bill->Date == Date)
        {
            cout << setw(21) << "|";
            cout << setw(9) << node_bill->Bill->Name_Product;
            cout << setw(20) << node_bill->Bill->Quantity;
            cout << setw(30) << node_bill->Bill->Price;
            cout << setw(10) << "|"  << endl;
            Total_amount += node_bill->Bill->Amount;
        }    
        node_bill = node_bill->pnext;
    }
    cout << setw(21) << "|";
    cout << setw(69) << "|"  << endl;
    cout << setw(21) << "|";
    cout << setw(69) << "|"  << endl;
    cout << setw(21) << "|";
    cout << setw(69) << "|"  << endl;
    cout << setw(21) << "|";
    cout << setw(69) << "|"  << endl;
    cout << setw(21) << "|";
    cout << setw(69) << "|"  << endl;
    cout << setw(20) << "";
    for(int i = 0; i<w;i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << setw(30) << "Total";
    cout << setw(50) << Total_amount;
    cout << "\n\n\t\t\t\t\t\tSEE YOU LATER " << endl;
    cout << "\t\t\t\t\t\t************** \n";
}
int main()
{
    bool done_object = true, done_class = true;
    int encode, object;
    string id;
    LIST lst;
    Initialize(lst);
    while (done_object)
    {
    	SetColor(0,12);
        done_class = true;
        cout << "\n\n\t\t\t\t\t\t\tGroup 10:\n";
        cout << "\t\t\t\t\t\t\tBui Tuan Dat         19119039\n";
        cout << "\t\t\t\t\t\t\tLe Thi Kieu Giang    19119001\n";
        cout << "\t\t\t\t\t\t\tNguyen Hung Thinh    19119056\n";
        SetColor(0, 15);
        cout << "\n\n\t\t\t\t\t\tWELCOME TO ADS SHOP " << endl;
        cout << "\t\t\t\t\t\t*******************";
        SetColor(0,9);
		cout << "\n\n\t\t\t|============ WELCOME TO STORE MANAGEMENT SYSTEM ============|\n";
        cout << "\n\t\t\t\t\t\t0. MANAGE STAFF " << endl;
        cout << "\t\t\t\t\t\t1. MANAGE PRODUCT " << endl;
        cout << "\t\t\t\t\t\t2. MANAGE CUSTOM" << endl;
        cout << "\t\t\t\t\t\t3. BUY PRODUCT" << endl;
        cout << "\t\t\t\t\t\t4. STOP PROCESS " << endl;
        cout << "\t\t\t\t\t\tCHOOSE OBJECT BELOW : ";
        cin >> object;
        if (object == 4)// Break
        {
            done_object = false;
            break;
        }
        while (done_class)
        {
            if (object == 0)
            {
            	SetColor(0,14);
                cout << "\n\n\t\t\t|============ WELCOME TO STAFF MANAGEMENT SYSTEM ============|\n";
                cout << "\n\t\t\t\t\t0. STOP PROCESS" << endl;
                cout << "\t\t\t\t\t1. ADDING STAFF " << endl;
                cout << "\t\t\t\t\t2. PRINT LIST STAFF " << endl;
                cout << "\t\t\t\t\t3. FINDDING ENCODE STAFF" << endl;
                cout << "\t\t\t\t\t4. DELETE STAFF" << endl;
                cout << "\t\t\t\t\t5. SORT STAFF" << endl;
                cout << "\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";
                cin >> encode;
                if (encode == 0)
                {
                    done_class = false;
                }
                else
                if (encode == 1)
                {
                    cout << "\n\t\t\t\t\tADDING STAFF" << endl;
                    InsertHead(lst, 0);
                }
                else
                if (encode == 2)
                {
                    int encode1;
                    cout << "\t\t\t\t\t===================================" << endl;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\tPRINT LIST STAFF" << endl;
                    cout << "\t\t\t\t\t0. LOAD STAFF FROM CSV" << endl;
                    cout << "\t\t\t\t\t1. PRINT STAFF AND SAVE TO CSV"<< endl;
                    cout << "\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        Load_csv(lst,0);
                        PrintList(lst, 0);
                    }
                    else
                    if (encode1 == 1)
                    {
                        PrintList(lst, 0);
                    }
                }
                if (encode == 3)
                {
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\tFINDDING ENCODE STAFF" << endl;
                    cout << "\t\t\t\t\tINPUT ID: ";
                    cout << "\n\t\t\t\t\t";
                    cin >> id;
                    PrintSearch_NV(lst, id);
                }
                else
                if (encode == 4)
                {
                    string QR_NV;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\tENTER TO DELETE QR: " << endl;
                    cout << "\t\t\t\t\t";
                    cin >> QR_NV;
                    Delete_NV(lst, QR_NV);
                }
                else
                if (encode == 5)
                {
                    int encode1;
                    cout << "\t\t\t\t\t===================================" << endl;
                    SetColor(0,11);
                    cout << "\t\t\t\t\t0. ASCENDING" << endl;
                    cout << "\t\t\t\t\t1. DESCENDING"<< endl;
                    cout << "\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        SortList(lst,"STAFF","ID",0);
                        cout << "\n\t\t\t\t\t->SORT ASCENDING COMPLETE";
                    }
                    else
                    if (encode1 == 1)
                    {
                        SortList(lst,"STAFF","ID",1);
                        cout << "\n\t\t\t\t\t->SORT DESCENDING COMPLETE";
                    }
                }                
            }
            if (object == 1)
            {
            	SetColor(0,14);
                cout << "\n\n\t\t\t|============ WELCOME TO PRODUCT MANAGEMENT SYSTEM ============|\n";
                cout << "\n\t\t\t\t\t\t0. STOP PROCESS" << endl;
                cout << "\t\t\t\t\t\t1. ADDING PRODUCT " << endl;
                cout << "\t\t\t\t\t\t2. PRINT LIST PRODUCT " << endl;
                cout << "\t\t\t\t\t\t3. DELETE PRODUCT" << endl;
                cout << "\t\t\t\t\t\t4. FINDING PRODUCT" << endl;
                cout << "\t\t\t\t\t\t5. SORT PRODUCT" << endl;
                cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";
                cin >> encode;
                if (encode == 0)
                {
                    done_class = false;
                }
                else
                if (encode == 1)
                {
                    cout << "\n\t\t\t\t\tADDING PRODUCT" << endl;
                    InsertHead(lst, 1);
                }
                else
                if (encode == 2)
                {
                    int encode1;
                    cout << "\t\t\t\t\t===================================" << endl;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\t\tPRINT LIST PRODUCT" << endl;
                    cout << "\t\t\t\t\t\t0. LOAD PRODUCT FROM CSV" << endl;
                    cout << "\t\t\t\t\t\t1. PRINT PRODUCT AND SAVE TO CSV"<< endl;
                    cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        Load_csv(lst,1);
                        PrintList(lst, 1);
                    }
                    else
                    if (encode1 == 1)
                    {
                        PrintList(lst, 1);
                    }
                }
                else
                if (encode == 3)
                {
                    string QR_product;
                     SetColor(0,11);
                    cout << "\n\t\t\t\t\tENTER TO DELETE QR: " << endl;
                    cout << "\t\t\t\t\t";
                    cin >> QR_product;
                    Delete_SP(lst, QR_product);
                }
                else
                if (encode == 4)
                {
                    string id;
                     SetColor(0,11);
                    cout << "\n\t\t\t\t\tFINDING PRODUCT " << endl;
                    cout << "\t\t\t\t\tINPUT ID: ";
                    cout << "\n\t\t\t\t\t";
                    cin >> id;
                    PrintSearch_SP(lst, id);
                }
                else
                if (encode == 5)
                {
                    int encode1;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\t\t0. ASCENDING" << endl;
                    cout << "\t\t\t\t\t\t1. DESCENDING"<< endl;
                    cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        SortList(lst,"PRODUCT","ID",0);
                        cout << "\t\t\t\t\t\t->SORT ASCENDING COMPLETE";
                    }
                    else
                    if (encode1 == 1)
                    {
                        SortList(lst,"PRODUCT","ID",1);
                        cout << "\t\t\t\t\t\t->SORT DESCENDING COMPLETE";
                    }
                }
            }
            if (object == 2)
            {
            	SetColor(0,14);
                cout << "\n\n\t\t\t|============ WELCOME TO CUSTOMER MANAGEMENT SYSTEM ============|\n";
                cout << "\n\t\t\t\t\t\t0. STOP PROCESS" << endl;
                cout << "\t\t\t\t\t\t1. ADDING CUSTOMER " << endl;
                cout << "\t\t\t\t\t\t2. PRINT LIST CUSTOMER " << endl;
                cout << "\t\t\t\t\t\t3. DELETE CUSTOMER" << endl;
                cout << "\t\t\t\t\t\t4. SORT CUSTOMER" << endl;
                cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";
                cin >> encode;
                if (encode == 0)
                {
                    done_class = false;
                }
                else
                if (encode == 1)
                {
                    cout << "\n\t\t\t\t\tADDING CUSTOMER" << endl;
                    InsertHead(lst, 2);
                }
                if (encode == 2)
                {
                    int encode1;
                    cout << "\t\t\t\t\t===================================" << endl;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\t\tPRINT LIST CUSTOMER" << endl;
                    cout << "\t\t\t\t\t\t0. LOAD CUSTOMER FROM CSV" << endl;
                    cout << "\t\t\t\t\t\t1. PRINT CUSTOMER AND SAVE TO CSV"<< endl;
                    cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        Load_csv(lst,2);
                        PrintList(lst, 2);
                    }
                    else
                    if (encode1 == 1)
                    {
                        PrintList(lst, 2);
                    }
                }
                else
                if (encode == 3)
                {
                    string QR_KH;
                    SetColor(0,11);
                    cout << "\n\t\t\t\t\tENTER CUSTOMER ID TO DELETE: " << endl;
                    cout << "\t\t\t\t\t";
                    cin >> QR_KH;
                    Delete_KH(lst, QR_KH);
                }
                if (encode == 4)
                {
                    int encode1;
                    SetColor(0,11);
                    cout << "\t\t\t\t\t\t0. ASCENDING" << endl;
                    cout << "\t\t\t\t\t\t1. DESCENDING"<< endl;
                    cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";                    
                    cin >> encode1;
                    if(encode1 == 0)
                    {
                        SortList(lst,"CUSTOMER","ID",0);
                        cout << "\t\t\t\t\t\t->SORT ASCENDING COMPLETE";
                    }
                    else
                    if (encode1 == 1)
                    {
                        SortList(lst,"CUSTOMER","ID",1);
                        cout << "\t\t\t\t\t\t->SORT DESCENDING COMPLETE";
                    }
                }
                
            }
            if (object == 3)
            {
            	SetColor(0,14);
                cout << "\n\n\t\t\t|============ WELCOME TO BUY MANAGEMENT SYSTEM ============|\n";
                cout << "\n\t\t\t\t\t\t0. STOP PROCESS" << endl;
                cout << "\t\t\t\t\t\t1. UPDATE PRODUCTS " << endl;
                cout << "\t\t\t\t\t\t2. BUY PRODUCT " << endl;
                cout << "\t\t\t\t\t\t3. PRINT BILL " << endl;
                cout << "\t\t\t\t\t\t4. STATISTIC" << endl;
                cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";
                cin >> encode;
                if (encode == 0)
                {
                    done_class = false;
                }
                else
                if (encode == 1) //UPDATE PRODUCTS
                {
                    PrintList(lst, 1);
                }
                else
                if (encode == 2)
                {
                    SetColor(0,11);
                    string input_qr, id_custom;
                    InsertHead(lst,3);
                    int k;
                    cout << "\t\t\t\t\tWHAT DO YOU WANT(INPUT QR_SP): ";
                    cin >> input_qr;
                    cout << "\t\t\t\t\tHOW MUCH DO YOU WANT: ";
                    cin >> k;
                    PrintList(lst,2);
                    cout << "\t\t\t\t\tID KHACH HANG MUA HANG: ";
                    cin >> id_custom;
                    Buy_SP(lst, input_qr, id_custom, k);
                }
                else
                if(encode == 3)
                {
                    string id_custom, Date;
                    PrintList(lst,3);
                    cout << "\t\t\t\t\tENTER ID OF CUSTOMER: ";
                    cin >> id_custom;
                    cout << "\t\t\t\t\tENTER DAY/MONTH/YEAR: ";
                    cin >> Date;
                    Export_Bill(lst,id_custom,Date);
                }
                else
                if (encode == 4)
                    {
                        bool done_class1 = true;
                        int encode1;
                        while (done_class1)
                        {
                            SetColor(0,11);
                            cout << "\n\n\t\t\t|============ WELCOME TO STATISTIC SYSTEM ============|\n";
                            cout << "\n\t\t\t\t\t\t0. STOP PROCESS" << endl;
                            cout << "\t\t\t\t\t\t1. PRINT AND UPDATE FROM CSV" << endl;
                            cout << "\t\t\t\t\t\t2. PRINT FROM SYSTEM" << endl;
                            cout << "\t\t\t\t\t\tENTER SITUATION TO RUN THIS STATE: ";
                            cin >> encode1;
                            if (encode1 == 0)
                            {
                                done_class1 = false;
                            }
                            else
                            if (encode1 == 1)
                            {
                                Load_csv(lst,3);
                                PrintList(lst, 3);
                            }
                            else
                            if (encode1 == 2)
                            {
                                PrintList(lst, 3);
                            }
                        }
                    }
            }
        }
    }
    return 0;
}