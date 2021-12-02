// List ADT
typedef struct CallList {
        int currentSize;
        int maxSize;
        int *entries;
} CallList;

// Function Prototypes
CallList initialize(int maxSize);
int add(int item, CallList *list);
void print(CallList list);
int check(int item, CallList *list);
