#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

// Function declarations

// Functionalities [main.c]
void init_intitalization(AddressBook *);
int create_contact(AddressBook *);
void list_contacts(AddressBook *);
int search_contacts(AddressBook *);
int edit_contact(AddressBook *);
int delete_contact(AddressBook *);
int save_contacts(AddressBook *);

// Sub-Functions [contact.c]
void print_contact_details(AddressBook *, int, int);
int search_by_name(int check, AddressBook *);
int search_by_mobile_no(AddressBook *);
int search_by_mail(AddressBook *);
void delete_shift(AddressBook *, int);
void print_line(void);

//Validations [Validations.c]
char *name_validation(char *name);
char *mobile_no_validation(int check, char *mobile_no,AddressBook *addressbook);
char *mail_id_validation(int check, char *mail_id, AddressBook *addressbook);

#endif // CONTACT_H
       // CONTACT_H