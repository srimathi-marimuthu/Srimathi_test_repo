#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"contact.h"

char *name_validation(char *name)  // validation for name
{
    int count = 0;

    while(1)
    {
        if(!count)
        {
            printf("Enter Name: ");
            count++;
        }
        else printf("Enter Name again: ");

        scanf("%[^\n]%*c",name);

        int i=0,flag=0;
        while(name[i])  //only alphabets and space
        {
            if(isalpha(name[i]) || name[i] == ' ') i++;
            else 
            {
                printf("\033[1;31mName should contain only alphabets and spaces! Try again.\033[0m\n");
                flag = 1;
                break;
            }
        }
        if(flag) continue;
        return name;
    }
}

char *mobile_no_validation(int check, char *mobile_no, AddressBook *addressbook)  // validation for mobile number
{
    int count = 0,i=0,flag=0;

    while(1)
    {
        if(!count)
        {
            printf("Enter Mobile number: ");
            count++;
        }
        else printf("Enter Mobile number again: ");

        scanf("%[^\n]%*c",mobile_no);

        i=0,flag=0;
        while(mobile_no[i])
        {
            if(isdigit(mobile_no[i])) i++;  //only numbers
            else
            {
                printf("\033[1;31mMobile number should contain only numbers! Try again.\033[0m\n");
                flag = 1;
                break;
            }
        }
        if(flag) continue;

        if(strlen(mobile_no) != 10)  // mobile no should be 10 digits long
        {
            if(strlen(mobile_no)>10) printf("\033[1;31mMobile number should only have 10 digits! Try again.\033[0m\n");
            
            if(strlen(mobile_no)<10) printf("\033[1;31mMobile number must have 10 digits! Try again.\033[0m\n");
            continue;
        }

        if(!(*mobile_no >= '6' && *mobile_no <= '9'))  // first number should be in range from 6 to 9
        {
            printf("\033[1;31mFirst number of Mobile number should be in range of 6 to 9! Try again.\033[0m\n");
            continue;
        }

        if(check)
        {
            flag = 0;
            for(int i=0; i<addressbook->contact_count; i++)  //number should be unique
            {
                if(!strcmp(mobile_no,addressbook->contact_details[i].Mobile_number))
                {
                    printf("\033[1;31mEntered Mobile number already exists!\nMobile number must be unique.\033[0m\nTry another number.\n");
                    flag = 1;
                    break;
                }
            }
            if(flag) continue;
        }

        return mobile_no;
    }
}

char *mail_id_validation(int check, char *mail_id, AddressBook *addressbook)
{
    int count = 0,flag = 0;

    while(1)
    {
        flag = 0;
        if(!count)
        {
            printf("Enter Mail Id: ");
            count++;
        }
        else printf("Enter Mail Id again: ");

        scanf("%[^\n]%*c",mail_id);

        if(strchr(mail_id,'@') == NULL)  //Atleast one @ is present
        {
            printf("\033[1;31mOne @ symbol must be present! Try again.\033[0m\n");
            continue;
        }

        if(strchr(mail_id,'@') == mail_id) // Atleast one letters present before @
        {
            printf("\033[1;31mMail Id should not start with @ symbol! Try again.\033[0m\n");
            continue;
        }

        if(strchr(mail_id,'@') != strrchr(mail_id,'@'))  //only single @ is present 
        {
            printf("\033[1;31mOnly one @ symbol should be in the Mail Id! Try again.\033[0m\n");
            continue;
        }

        if( (strstr(strchr(mail_id,'@'),".com") == NULL || (*(strstr(strchr(mail_id,'@'),".com")+4) != '\0')) && 
        (strstr(strchr(mail_id,'@'),".in") == NULL || (*(strstr(strchr(mail_id,'@'),".in")+3) != '\0')) )// has either ".com" or ".in" at the last 
        {
            printf("\033[1;31mEither \".com\" or \".in\" must be present at the last of the Mail Id only once! Try again.\033[0m\n");
            continue;
        }
                    
        if( (strchr(mail_id,'@')+1 == strstr(mail_id,".com")) || //Domin name should be present
            (strchr(mail_id,'@')+1 == strstr(mail_id,".in")) )
        {
            printf("\033[1;31mDomain name should be present after @ symbol! Try again.\033[0m\n");
            continue;
        }

        int i = 0;
        while(mail_id[i])
        {
            if(mail_id[i] == '@')
            {
                i++;
                break;
            }
            i++;
        }
        while(mail_id[i])  //Domain name should not have numbers
        {
            if(isdigit(mail_id[i])) 
            {
                printf("\033[1;31mDomain name should not have numbers! Try again.\033[0m\n");
                break;
            }
            i++;
        }
        if(mail_id[i] != '\0') continue;

        i=0;
        while(mail_id[i])  //should contain only lowercase, numbers, '@' and (.)
        {
            if((islower(mail_id[i])) || mail_id[i] == '@' || mail_id[i] == '.' || isdigit(mail_id[i])) i++;
            else 
            {
                printf("\033[1;31mMail Id should only contain '@' symbol, full stop (.), numbers and lowercase letters! Try again.\033[0m\n");
                break;
            }
        }
        if(mail_id[i] != '\0') continue;

        if(check)
        {
            for(int i=0; i<addressbook->contact_count; i++)  //mail id must be unique
            {
                if(!strcmp(mail_id,addressbook->contact_details[i].Mail_ID))
                {
                    printf("\033[1;31mEntered Mail Id already exists!\nMail Id must be unique.\033[0m\nTry another Mail Id.\n");
                    flag = 1;
                    break;
                }
            }
            if(flag) continue;
        }

        return mail_id;
    }
}