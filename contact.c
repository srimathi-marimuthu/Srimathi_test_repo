#include <stdio.h>
#include <string.h>
#include "contact.h"
#include <stdio_ext.h>

int count=0,arr[10]={0};

// Function definitions

void init_intitalization(AddressBook *addressbook)  //reading contacts from file
{
    FILE *fp = fopen("AddressBook.csv", "r");
    if (fp == NULL) 
    {
        printf("No saved data found. Initializing with defaults.\n");
        addressbook->contact_count = 0;
    }
    else 
    {
        fscanf(fp, "#%d\n", &addressbook->contact_count);  //no of contacts

        for (int i = 0; i < addressbook->contact_count; i++)   //reading contacts
        {
            fscanf(fp, " %31[^,], %10[^,], %34[^\n]\n", 
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
        }
        fclose(fp);
    }
}
int create_contact(AddressBook *addressbook)  //adding contact function
{
    while(1)
    {
        printf("\n");
        char yn;
        char name[32];
        strcpy(addressbook->contact_details[addressbook->contact_count].Name,name_validation(name));

        char number[11];
        strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number,mobile_no_validation(1,number,addressbook));

        char mail_id[35];
        strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID,mail_id_validation(1,mail_id,addressbook));

        addressbook->contact_count++;

        printf("\033[1;32mContact Added Successfully!\033[0m\n\n");

        printf("\033[0;33mDo you want to continue? (y/n) :\033[0m");
        scanf("%c%*c",&yn);

        if(yn == 'y') continue;
        else if(yn == 'n') return 0;
        else
        {
            printf("\033[0;31mInvalid Option!\033[0m");
            __fpurge(stdin);
        }
    }
}
void list_contacts(AddressBook *addressbook)  //list function
{
    printf("\n");
    print_line();
    printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
    print_line();

    int s=1;
    for(int i=0;i<addressbook->contact_count;i++)  //loop to print all the contacts
    {
        print_contact_details(addressbook,i,s++);
    }

    print_line();
}

int search_contacts(AddressBook *addressbook)  // search function
{
    int option,val;

    while(1)
    {
        printf("\n");
        printf("Search Contact menu : \n1. Name \n2. Mobile number\n3. Mail ID\n4. Exit\n\nEnter the option : "); /* Providing menu */

        scanf("%d%*c",&option);

        switch(option)
        {
            case 1:
            val = search_by_name(0,addressbook);

            if(val >= 0)
            {
                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);
                
                print_line();
                printf("\n");
            }
            break;

            case 2:
            val = search_by_mobile_no(addressbook);

            if(val >= 0)
            {
                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);
                
                print_line();
                printf("\n");
            }
            break;

            case 3:
            val = search_by_mail(addressbook);

            if(val >= 0)
            {
                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);
                
                print_line();
                printf("\n");
            }
            break;

            case 4:
            return 0;

            default:
            printf("\033[1;31mInvalid Option!\033[0m\n");
            __fpurge(stdin);
            break;

        }
    }
}
int edit_contact(AddressBook *addressbook)  //edit function
{
    int option,val;
    char yn,name[32],number[11],mail_id[35];

    while(1)  //search option for edit
    {
        printf("\n");
        printf("Search Contact to edit : \n1. Name \n2. Mobile number\n3. Mail ID\n4. Exit\n\nEnter the option : ");  //providing menu to select how to search the contact to edit 

        scanf("%d%*c",&option);
        printf("\n");

        switch(option)
        {
            case 1:
            {
                val = search_by_name(1,addressbook);
                break;
            }

            case 2:
            {
                val = search_by_mobile_no(addressbook);
                break;
            }

            case 3:
            {
                val = search_by_mail(addressbook);
                break;
            }

            case 4:
            return 0;

            default:
            printf("\033[1;31mInvalid Option!\033[0m\n");
            __fpurge(stdin);
            continue;
        }

        if(val<0) continue;
        
        printf("\nEdit Contact menu : \n1. Name \n2. Mobile number\n3. Mail ID\n4. All details\n\nEnter the option : "); // providing menu to select the member to be edited

        scanf("%d%*c",&option);

        switch(option)
        {
            case 1:
            
            if(val >= 0)
            {
                printf("\n"); 
                
                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);

                print_line(); 

                printf("\n\033[0;33mEdit this contact's Name? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y')
                {
                    strcpy(addressbook->contact_details[val].Name,name_validation(name));
                    
                    printf("\n\033[1;32mContact's Name has been changed successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                }
            }
            break;

            case 2:
            
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);

                print_line(); 

                printf("\n\033[0;33mEdit this contact's Mobile number? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y')
                {
                    strcpy(addressbook->contact_details[val].Mobile_number,mobile_no_validation(1,number,addressbook));

                    printf("\n\033[1;32mContact's Mobile number has been changed successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                }
            }
            break;

            case 3:
            
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);
                
                print_line();

                printf("\n\033[0;33mEdit this contact's Mail Id (y/n): \033[0m]");
                scanf("%c%*c",&yn);

                if(yn == 'y')
                {
                    strcpy(addressbook->contact_details[val].Mail_ID,mail_id_validation(1,mail_id,addressbook));

                    printf("\n\033[1;32mContact's Mail Id has been changed successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                }
            }
            break;

            case 4:
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);
                
                print_line();

                printf("\n\033[0;33mEdit all the details of this contact? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y')
                {
                    strcpy(addressbook->contact_details[val].Name,name_validation(name));

                    strcpy(addressbook->contact_details[val].Mobile_number,mobile_no_validation(1,number,addressbook));

                    strcpy(addressbook->contact_details[val].Mail_ID,mail_id_validation(1,mail_id,addressbook));
                    
                    printf("\n\033[1;32mAll the details of the contact has been changed successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                    __fpurge(stdin);
                }
            }

            default:
            printf("\033[1;31mInvalid Option!\033[0m");
            __fpurge(stdin);
            continue;
        }
    }
}

int delete_contact(AddressBook *addressbook)  //delete function
{
    int option,val;
    char yn;

    while(1)
    {
        printf("\n");

        printf("Delete Contact by : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\n\nEnter the option : "); /* Providing menu */

        scanf("%d%*c",&option);

        switch(option)
        {
            case 1:
            val = search_by_name(1,addressbook);
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);

                print_line();
                printf("\n");

                printf("\033[0;33mDelete this contact? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y') 
                {
                    delete_shift(addressbook,val);
                    printf("\n\033[1;32mContact deleted successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                }
            }
            break;

            case 2:
            val = search_by_mobile_no(addressbook);
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);

                print_line();
                printf("\n");

                printf("\033[0;33mDelete this contact? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y') 
                {
                    delete_shift(addressbook,val);
                    printf("\n\033[1;32mContact deleted successfully!\033[0m\n");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                    __fpurge(stdin);
                }
            }
            break;

            case 3:
            val = search_by_mail(addressbook);
            if(val >= 0)
            {
                printf("\n");

                print_line();
                printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
                print_line();

                print_contact_details(addressbook,val,1);

                print_line();
                printf("\n");

                printf("\033[0;33mDelete this contact? (y/n): \033[0m");
                scanf("%c%*c",&yn);

                if(yn == 'y') 
                {
                    delete_shift(addressbook,val);
                    printf("\n\033[1;32mContact deleted successfully!\033[0m");
                }
                else if(yn == 'n') break;
                else
                {
                    printf("\033[0;31mInvalid Option!\033[0m");
                    __fpurge(stdin);
                }
            }
            break;

            case 4:
            return 0;

            default:
            printf("\033[1;31mInvalid Option!\033[0m");
            __fpurge(stdin);
            break;

        }
    }
    return 0;
}
int save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("AddressBook.csv","w");
    fprintf(fp, "#%d\n", addressbook->contact_count);
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        fprintf(fp, "%s, %s, %s\n", 
        addressbook->contact_details[i].Name,
        addressbook->contact_details[i].Mobile_number,
        addressbook->contact_details[i].Mail_ID);
    }
    fclose(fp);
    return 0;
}


//sub-functionalities:

int search_by_name(int check, AddressBook *addressbook)  //search by name function
{
    char input[32], yn;

    while(1)
    {
        count = 0;
        strcpy(input,name_validation(input));

        for(int i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(input,addressbook->contact_details[i].Name) == 0)
            {
                arr[count] = i;
                count++;
            }
        }

        if(count == 1) return *arr;
        else if(count == 0)
        {
            printf("\033[0;31mName not found!\033[0m\nTry again ? (y/n):");
            scanf("%c%*c",&yn);

            if(yn == 'y') continue;
        }
        else   // contacts with duplicate names
        {
            print_line();
            printf("\033[1;36m%-5s %-35s %-20s %-35s\033[0m\n","S.No","Name","Mobile Number","Mail Id");
            print_line();

            int s=1;
            for(int i=0;i<count;i++)
            {
                print_contact_details(addressbook, arr[i], s++);
            }
            print_line();

            if(check)
            {
                while(1)
                {
                    printf("Select the contact: ");
                    int s_no;
                    scanf("%d%*c",&s_no);
                    if(s_no > count)
                    {
                        printf("\n\033[0;31mSelect the contact from the above %d contacts!\033[0m\n\n",count);
                        continue;
                    }
                    return arr[s_no-1];
                }
            }
        }
        return -1;
    }
}

int search_by_mobile_no(AddressBook *addressbook)  //search by mobile number function
{
    char input[11], yn;

    while(1)
    {
        strcpy(input,mobile_no_validation(0,input,addressbook));


        for(int i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(input,addressbook->contact_details[i].Mobile_number) == 0) return i;
        }

        printf("\033[1;31mMobile Number not found!\033[0m\nTry again ? (y/n):");
        scanf("%c%*c",&yn);

        if(yn == 'y') continue;
        else return -1;
    }
}

int search_by_mail(AddressBook *addressbook)  //search by mail id function
{
    char input[35], yn;

    while(1)
    {
        strcpy(input,mail_id_validation(0,input,addressbook));

        for(int i=0;i<addressbook->contact_count;i++)
        {
            if(strcmp(input,addressbook->contact_details[i].Mail_ID) == 0) return i;
        }

        printf("\033[1;31mMail Id not found!\033[0m\nTry again ? (y/n): ");
        scanf("%c%*c",&yn);

        if(yn == 'y') continue;
        else return -1;
    }
}

void print_contact_details(AddressBook *addressbook, int i,int serial)  // function to print contact details
{
    printf("\033[0;36m%-5d %-35s %-20s %-35s\033[0m\n",serial,
            addressbook->contact_details[i].Name,
            addressbook->contact_details[i].Mobile_number,
            addressbook->contact_details[i].Mail_ID);
}

void delete_shift(AddressBook *addressbook, int i)  // shifting funtion for deleting contact
{
    for(i;i<addressbook->contact_count;i++)
    {
        strcpy(addressbook->contact_details[i].Name,addressbook->contact_details[i+1].Name);
        strcpy(addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i+1].Mobile_number);
        strcpy(addressbook->contact_details[i].Mail_ID,addressbook->contact_details[i+1].Mail_ID);
    }
    addressbook->contact_count--;
}

void print_line(void)  // printing lines for format
{
    for(int i=0;i<90;i++)
    {
        printf("%c",'.');
    }

    printf("\n");
}