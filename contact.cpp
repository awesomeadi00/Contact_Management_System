#include "contact.h"

//Default constructor: initializes all the attributes of a contact.
Contact::Contact(string Fname, string Lname, string Email, string Phone, string City, string Country, bool IsFav) {
    fname = Fname;
    lname = Lname;
    email = Email;
    primaryPhone = Phone;
    city = City;
    country = Country;
    isFav = IsFav;
}
