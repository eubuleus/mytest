//C++ Notes: Array Initialization

//An array can be initialized in the declaration by writing a comma-separated list of values enclosed in braces following an equal sign.

int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

//Altho this looks like an assignment, assignment statements with arrays are not allowed, and this syntax is legal only in a declaration.


//Size can be set from initial value list
//If the size is omitted, the compiler uses the number of values. For example,
// is the same as the statement below:
int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

// No default value
// If an array has no initialization, the values are undefined.

float pressure[10];   // Initial values of pressure undefined.

// Missing initialization values use zero
//If an explicit array size is specified, but an shorter initiliazation list is specified, the unspecified elements are set to zero.

float pressure[10] = {2.101, 2.32, 1.44};

//This not only initializes the first three values, but all remaining elements are set to 0.0. To initialize an array to all zeros, initialize only the first value.

float p1[1000];         // No intitialization.
float p2[1000] = {0.0}; // All 1000 values initialized to zero.

//Initialization of character arrays
//Character arrays can be initialized on the right by writing a double-quoted string.

char greeting[100] = "Hello"; // Remaining characters zero.
char goodbye[] = "Adios";     // Array size is 6 (final zero on strings).
