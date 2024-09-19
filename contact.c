#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount != 0)  // Check if there are any contacts
    {
	printf("Listing all contacts:\n");
	printf("S.No\tName\t\tPhone Number\t\tEmail ID\n");
	for (int i = 0; i <addressBook->contactCount; i++)  // Loop through contacts
	{
	    printf("%d.",i+1);  // Print the contact number (1-based index)
	    printf("\t%s\t", addressBook->contacts[i].name);  // Print the contact name
	    printf("\t%s\t", addressBook->contacts[i].phone);  // Print the phone number
	    printf("\t%s\n", addressBook->contacts[i].email);  // Print the email
	    printf("\n");
	}
    }
    else
    {
	printf("No contacts found\n");  // Message if no contacts are found
	return;
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;  // Initialize contact count to zero
    FILE *file=fopen("file.txt","r");  // Open file in read mode
    if(file==NULL)  // Check if file exists
    {
	printf("File not exist");
	return;
    }
    char new[200];  // Temporary buffer to store each line
    while(fscanf(file,"%[^\n]",new)==1)  // Read each line from the file
    {
	char *name=strtok(new,",");  // Extract name
	char *phone=strtok(NULL,",");  // Extract phone number
	char *email=strtok(NULL,"\n");  // Extract email ID
	if((name!=NULL) && (phone !=NULL) && (email!=NULL) && addressBook->contactCount<100)  // Check if values are valid and within limit
	{
	    strcpy(addressBook->contacts[addressBook->contactCount].name,name);  // Copy name to the contact list
	    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);  // Copy phone number to the contact list
	    strcpy(addressBook->contacts[addressBook->contactCount].email,email);  // Copy email ID to the contact list
	    addressBook->contactCount++;  // Increment contact count
	}
	fseek(file,1,SEEK_CUR);  // Move file pointer to the next line

    }
    fclose(file);  // Close the file
}

void saveAndExit(AddressBook *addressBook)   // function for saving contacts from addressbook to file.txt
{
    FILE *file = fopen("file.txt", "w");  //Opening file using fopen
    if(file == NULL)     //checking for file is opened or not
    {
	printf("Error: Could not open file\n");  //if file not opened then error message print 
	return;
    }
    for(int i = 0; i < addressBook->contactCount; i++)
    {
	fprintf(file, "%s,", addressBook->contacts[i].name);  //printing contact name to file 
	fprintf(file, "%s,", addressBook->contacts[i].phone); //printing phone no to file 
	fprintf(file, "%s", addressBook->contacts[i].email);  //printing maild id to file
	putc('\n', file);      //after printing every full contact atlast it prints /n to file
    }
    fclose(file);   //fclose is used to save file
    printf("Contacts saved to file successfully\n"); 
}
void createContact(AddressBook *addressBook)
{
    char nam[50], phoneno[20], mailid[20];  // Declare arrays to store the new contact's name, phone number, and email
    int flag = 0, flag1 = 0, flag2 = 0, i;  // Flags to ensure valid inputs and a loop counter 'i'

    printf("Enter the new contact Name\n");  
    getchar();                              // Clear input buffer
    scanf("%[^\n]", nam);                   // Read the name input with spaces

    printf("Enter the new contact phone no\n");
    getchar();                              // Clear input buffer
    scanf("%[0-9]", phoneno);               // Read only digits as the phone number

    printf("Enter the new contact mailid\n");
    getchar();                              // Clear input buffer
    scanf("%[^\n]", mailid);                // Read the email ID

    // Check if the entered name already exists in the AddressBook
    for (i = 0; i < addressBook->contactCount; i++)
    {
	int ret = strcmp(addressBook->contacts[i].name, nam);  // Compare the new name with existing names
	if (ret == 0)                                          // If a match is found, the name already exists
	{
	    printf("Invalid input: Name already exists\n");
	    return;                                            // Exit the function if the name is a duplicate
	}
    }
    flag = 1;  // Set the flag to indicate the name is unique

    // Check if the phone number is exactly 10 digits
    if (strlen(phoneno) == 10)
    {
	// Check if the entered phone number already exists
	for (i = 0; i < addressBook->contactCount; i++)
	{
	    int met = strcmp(addressBook->contacts[i].phone, phoneno);  // Compare the new phone number with existing numbers
	    if (met == 0)                                               // If a match is found, the phone number already exists
	    {
		printf("Invalid input: Phone number already exists\n");
		return;                                                 // Exit if the phone number is a duplicate
	    }
	}
    }
    else
    {
	printf("Invalid input: Phone number should be exactly 10 digits\n");
	return;  // Exit if the phone number is not 10 digits
    }
    flag1 = 1;  // Set the flag to indicate the phone number is valid

    // Check if the email contains '@' and '.'
    if (strchr(mailid, '@') != NULL)  // Ensure the email contains '@'
    {
	if (strstr(mailid, ".") != NULL)  // Ensure the email contains '.'
	{
	    // Check if the entered email ID already exists
	    for (i = 0; i < addressBook->contactCount; i++)
	    {
		int mani = strcmp(addressBook->contacts[i].email, mailid);  // Compare the new email with existing emails
		if (mani == 0)                                              // If a match is found, the email already exists
		{
		    printf("Invalid input: Email already exists\n");
		    return;                                                 // Exit if the email is a duplicate
		}
	    }
	}
	else
	{
	    printf("Invalid input: Email must contain .\n");
	    return;  // Exit if the email doesn't contain '.'
	}
    }
    else
    {
	printf("Invalid input: Email must contain @\n");
	return;  // Exit if the email doesn't contain '@'
    }
    flag2 = 1;  // Set the flag to indicate the email is valid

    // If all checks are passed, add the new contact to the AddressBook
    if (flag == 1 && flag1 == 1 && flag2 == 1)
    {
	strcpy(addressBook->contacts[addressBook->contactCount].name, nam);      // Copy the name into the AddressBook
	strcpy(addressBook->contacts[addressBook->contactCount].phone, phoneno);  // Copy the phone number
	strcpy(addressBook->contacts[addressBook->contactCount].email, mailid);   // Copy the email
	addressBook->contactCount++;                                              // Increment the contact count
	printf("Contact added successfully\n");                                   
    }
}
void searchContact(AddressBook *addressBook) 
{
    printf("Enter which contact you want based on 1.Name, 2.Email ID: ");
    int option, i, j = 1, flag8 = 0;  // Variables for option selection, loop control, and flags
    scanf("%d", &option);  // Read the user's option
    getchar();  // Clear input buffer

    switch(option)  // Switch based on user-selected option
    {
	case 1:  // Search by name
	    {
		char arr1[20];  // Array to hold the entered name
		printf("Enter the name of the contact you want: ");
		scanf("%[^\n]", arr1);  // Read the name input (allows spaces)
		getchar();  // Clear input buffer

		// Iterate over the contacts to find matches based on the name
		for (i = 0; i < addressBook->contactCount; i++)
		{
		    if (strstr(addressBook->contacts[i].name, arr1) != NULL)// Check if entered name is a substring of any contact name
		    {
			printf("%d.", j);  // Print the match number
			printf("Name : %s\t", addressBook->contacts[i].name);  // Display the contact's name
			printf("Phone: %s\t", addressBook->contacts[i].phone);  // Display the contact's phone number
			printf("Email:%s\n", addressBook->contacts[i].email);  // Display the contact's email
			j++;  // Increment match counter
			flag8 = 1;  // Set the flag to indicate a match was found
		    }
		}

		// If no matches are found, print a message
		if (flag8 == 0)
		{
		    printf("Contact not found.\n");
		}
		break;
	    }

	case 2:  // Search by email ID
	    {
		char arr2[20];  // Array to hold the entered email
		int flag9 = 0;  // Flag to check if any contact is found

		printf("Enter the email ID of the contact you want: ");
		scanf("%s", arr2);  // Read the email input
		getchar();  // Clear input buffer

		// Iterate over the contacts to find matches based on the email
		for (i = 0; i < addressBook->contactCount; i++)
		{
		    if (strstr(addressBook->contacts[i].email, arr2))  // Check if entered email is a substring of any contact email
		    {
			printf("Name : %s\t", addressBook->contacts[i].name);  // Display the contact's name
			printf("Phone:%s\t", addressBook->contacts[i].phone);  // Display the contact's phone number
			printf("Email:%s\n", addressBook->contacts[i].email);  // Display the contact's email
			flag9 = 1;  // Set the flag to indicate a match was found
		    }
		}

		// If no matches are found, print a message
		if (flag9 == 0)
		{
		    printf("Contact not found.\n");
		}
	    }
	    break;

	default:  // Handle invalid option input
	    printf("Invalid option selected.\n");
	    break;
    }
}
void editContact(AddressBook *addressBook)    // Function to edit contacts
{
    int i, choose, editno, flag = 0, j, k = 1, flag7 = 0, opt, manu = 0;
    printf("Select which contact you want to edit based on:\n1. Name\n2. Email\n");
    getchar();
    scanf("%d", &choose);   // Read option to edit by Name or Email

    char namarr[30], mailarr[30], editarr[30];  // Arrays for user input

    switch (choose)
    {
	case 1: // Edit by Name
	    printf("Enter contact name to edit: ");
	    getchar();
	    scanf("%[^\n]", namarr);  // Read name to search

	    // Display contacts matching the name
	    for (i = 0; i < addressBook->contactCount; i++)
	    {
		if (strstr(addressBook->contacts[i].name, namarr))  // Check if contact name contains the search string
		{
		    printf("%d.", k);
		    printf("Name : %s\t", addressBook->contacts[i].name);
		    printf("Phone:%s\t", addressBook->contacts[i].phone);
		    printf("Email:%s\n", addressBook->contacts[i].email);
		    manu = 1;  // Set flag to indicate that at least one match is found
		    k++;
		}
	    }

	    if (manu == 1)
	    {
		printf("Enter contact number based on the above list: ");
		scanf("%d", &opt);
		int index = 0;

		// Validate user choice and find the index of the selected contact
		if (opt < 1 || opt >= k)
		{
		    printf("Selected option is invalid\n");
		    return;
		}

		k = 1;  // Reset k for correct index assignment
		for (i = 0; i < addressBook->contactCount; i++)
		{
		    if (strstr(addressBook->contacts[i].name, namarr))
		    {
			if (k == opt)
			{
			    index = i;  // Store the index of the selected contact
			    break;
			}
			k++;
		    }
		}

		// Edit the selected contact's details
		do
		{
		    printf("Enter which data you want to edit:\n1. Name\n2. Phone No\n3. Email\n");
		    scanf("%d", &editno);
		    switch (editno)
		    {
			case 1:
			    {
				int gani = 0;
				printf("Enter new name to edit:\n");
				getchar();
				scanf("%[^\n]", editarr);

				// Check for duplicate names
				for (j = 0; j < addressBook->contactCount; j++)
				{
				    if (strcasecmp(addressBook->contacts[j].name, editarr) == 0)
				    {
					gani = 1;  // Duplicate name found
					break;
				    }
				}

				if (gani == 0)
				{
				    strcpy(addressBook->contacts[index].name, editarr);
				    flag7 = 1;
				    printf("Name edited successfully.\n");
				}
				else
				{
				    printf("Name already exists.\n");
				}
			    }
			    break;

			case 2:
			    {
				int gani = 0;
				printf("Enter new phone number to edit: ");
				getchar();
				scanf("%[0-9]", editarr);
				getchar();

				// Validate phone number length and check for duplicates
				if (strlen(editarr) == 10)
				{
				    for (j = 0; j < addressBook->contactCount; j++)
				    {
					if (strcmp(addressBook->contacts[j].phone, editarr) == 0)
					{
					    gani = 1;  // Duplicate phone number found
					    break;
					}
				    }

				    if (gani == 0)
				    {
					strcpy(addressBook->contacts[index].phone, editarr);
					flag7 = 1;
					printf("Phone number edited successfully.\n");
				    }
				    else
				    {
					printf("Phone number already exists.\n");
				    }
				}
				else
				{
				    printf("Invalid phone number.\n");
				}
			    }
			    break;

			case 3:
			    {
				int gani = 0;
				printf("Enter new email ID to edit: ");
				scanf("%s", editarr);
				getchar();

				// Validate email format and check for duplicates
				if (strchr(editarr, '@') != NULL && strstr(editarr, ".com") != NULL)
				{
				    for (j = 0; j < addressBook->contactCount; j++)
				    {
					if (strcasecmp(addressBook->contacts[j].email, editarr) == 0)
					{
					    gani = 1;  // Duplicate email ID found
					    break;
					}
				    }

				    if (gani == 0)
				    {
					strcpy(addressBook->contacts[index].email, editarr);
					flag7 = 1;
					printf("Email edited successfully.\n");
				    }
				    else
				    {
					printf("Email ID already exists.\n");
				    }
				}
				else
				{
				    printf("Invalid email address.\n");
				}
			    }
			    break;

			default:
			    printf("Invalid option.\n");
		    }
		} while (flag7 != 1);  // Repeat until a valid edit is made
	    }
	    else
	    {
		printf("Name not found.\n");
		return;
	    }
	    break;

	case 2: // Edit by Email
	    {
		int gani = 0, flag6 = 0;
		printf("Enter contact email to edit: ");
		getchar();
		scanf("%[^\n]", mailarr);
		getchar();

		// Display contacts matching the email
		for (i = 0; i < addressBook->contactCount; i++)
		{
		    if (strstr(addressBook->contacts[i].email, mailarr))
		    {
			printf("%d.", k);
			printf("Name : %s\t", addressBook->contacts[i].name);
			printf("Phone:%s\t", addressBook->contacts[i].phone);
			printf("Email:%s\n", addressBook->contacts[i].email);
			manu = 1;  // Set flag to indicate that at least one match is found
			k++;
		    }
		}

		if (manu == 1)
		{
		    printf("Enter contact number based on the above list: ");
		    scanf("%d", &opt);
		    int index = 0;

		    // Validate user choice and find the index of the selected contact
		    if (opt < 1 || opt >= k)
		    {
			printf("Selected option is invalid\n");
			return;
		    }

		    k = 1;  // Reset k for correct index assignment
		    for (i = 0; i < addressBook->contactCount; i++)
		    {
			if (strstr(addressBook->contacts[i].email, mailarr))
			{
			    if (k == opt)
			    {
				index = i;  // Store the index of the selected contact
				break;
			    }
			    k++;
			}
		    }

		    // Edit the selected contact's details
		    do
		    {
			printf("Enter data to edit in contacts:\n1. Name\n2. Phone No\n3. Email\n");
			scanf("%d", &editno);
			switch (editno)
			{
			    case 1:
				{
				    printf("Enter new name to edit: ");
				    getchar();
				    scanf("%[^\n]", editarr);

				    // Check for duplicate names
				    for (j = 0; j < addressBook->contactCount; j++)
				    {
					if (strcasecmp(addressBook->contacts[j].name, editarr) == 0)
					{
					    gani = 1;  // Duplicate name found
					    break;
					}
				    }

				    if (gani == 0)
				    {
					strcpy(addressBook->contacts[index].name, editarr);
					flag7 = 1;
					printf("Name edited successfully.\n");
				    }
				    else
				    {
					printf("Name already exists.\n");
				    }
				}
				break;

			    case 2:
				{
				    printf("Enter new phone number to edit: ");
				    getchar();
				    scanf("%[0-9]", editarr);
				    getchar();

				    // Validate phone number length and check for duplicates
				    if (strlen(editarr) == 10)
				    {
					for (j = 0; j < addressBook->contactCount; j++)
					{
					    if (strcmp(addressBook->contacts[j].phone, editarr) == 0)
					    {
						gani = 1;  // Duplicate phone number found
						break;
					    }
					}

					if (gani == 0)
					{
					    strcpy(addressBook->contacts[index].phone, editarr);
					    flag7 = 1;
					    printf("Phone number edited successfully.\n");
					}
					else
					{
					    printf("Phone number already exists.\n");
					}
				    }
				    else
				    {
					printf("Invalid phone number.\n");
				    }
				}
				break;

			    case 3:
				{
				    printf("Enter new email ID to edit: ");
				    scanf("%s", editarr);
				    getchar();

				    // Validate email format and check for duplicates
				    if (strchr(editarr, '@') != NULL && strstr(editarr, ".com") != NULL)
				    {
					for (j = 0; j < addressBook->contactCount; j++)
					{
					    if (strcasecmp(addressBook->contacts[j].email, editarr) == 0)
					    {
						gani = 1;  // Duplicate email ID found
						break;
					    }
					}

					if (gani == 0)
					{
					    strcpy(addressBook->contacts[index].email, editarr);
					    flag7 = 1;
					    printf("Email edited successfully.\n");
					}
					else
					{
					    printf("Email ID already exists.\n");
					}
				    }
				    else
				    {
					printf("Invalid email address.\n");
				    }
				}
				break;

			    default:
				printf("Invalid option.\n");
			}
		    } while (flag7 != 1);  // Repeat until a valid edit is made
		}
		else
		{
		    printf("Entered email not found.\n");
		}
	    }
	    break;

	default:
	    printf("Invalid option.\n");
	    break;
    }
}
void deleteContact(AddressBook *addressBook)
{
    int i, option, j, k = 1, opt;
    printf("Enter contact to delete based on:\n1. Name\n2. Phone no \n3. Email ID\n");
    getchar();
    scanf("%d", &option);

    switch (option)
    {
    case 1: // Delete contact by Name
        {
            char namearr[30];
            printf("Enter the name to delete contact: \n");
            getchar();
            scanf("%[^\n]", namearr);  // Read the name to search

            // Display contacts matching the name
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, namearr))  // Check if contact name contains the search string
                {
                    printf("%d. ", k);
                    printf("Name : %s\t", addressBook->contacts[i].name);
                    printf("Phone: %s\t", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    k++;
                }
            }

            // Prompt user to select a contact from the displayed list
            printf("Enter contact number based on the above list: ");
            scanf("%d", &opt);
            getchar();

            // Validate user choice and find the index of the selected contact
            if (opt < 1 || opt >= k)
            {
                printf("Selected option is invalid\n");
                return;
            }

            k = 1;  // Reset k for correct index assignment
            int index = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, namearr))
                {
                    if (k == opt)
                    {
                        index = i;  // Store the index of the selected contact
                        break;
                    }
                    k++;
                }
            }

            // Delete the selected contact by shifting subsequent contacts
            for (j = index; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;   
            printf("Contact deleted successfully.\n");
            return;
        }

    case 2: // Delete contact by Phone Number
        {
            char phonearr[20];
            printf("Enter the phone number to delete contact: \n");
            getchar();
            scanf("%[0-9]", phonearr);

            // Display contacts matching the phone number
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone, phonearr))  // Check if contact phone contains the search string
                {
                    printf("%d. ", k);
                    printf("Name : %s\t", addressBook->contacts[i].name);
                    printf("Phone: %s\t", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    k++;
                }
            }

            // Prompt user to select a contact from the displayed list
            printf("Enter contact number based on the above list: ");
            scanf("%d", &opt);
            getchar();

            // Validate user choice and find the index of the selected contact
            if (opt < 1 || opt >= k)
            {
                printf("Selected option is invalid\n");
                return;
            }

            k = 1;  // Reset k for correct index assignment
            int index = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].phone, phonearr))
                {
                    if (k == opt)
                    {
                        index = i;  // Store the index of the selected contact
                        break;
                    }
                    k++;
                }
            }

            // Delete the selected contact by shifting subsequent contacts
            for (j = index; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;   
            printf("Contact deleted successfully.\n");
            return;
        }

    case 3: // Delete contact by Email ID
        {
            char mailarr[30];
            printf("Enter the email ID to delete contact: \n");
            getchar();
            scanf("%s", mailarr);

            // Display contacts matching the email ID
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email, mailarr))  // Check if contact email contains the search string
                {
                    printf("%d. ", k);
                    printf("Name : %s\t", addressBook->contacts[i].name);
                    printf("Phone: %s\t", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    k++;
                }
            }

            // Prompt user to select a contact from the displayed list
            printf("Enter contact number based on the above list: ");
            scanf("%d", &opt);
            getchar();

            // Validate user choice and find the index of the selected contact
            if (opt < 1 || opt >= k)
            {
                printf("Selected option is invalid\n");
                return;
            }

            k = 1;  // Reset k for correct index assignment
            int index = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email, mailarr))
                {
                    if (k == opt)
                    {
                        index = i;  // Store the index of the selected contact
                        break;
                    }
                    k++;
                }
            }

            // Delete the selected contact by shifting subsequent contacts
            for (j = index; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--; 
            printf("Contact deleted successfully.\n");
            return;
        }

    default: // Handle invalid option
        printf("Selected option is not valid.\n");
        break;
    }
}

