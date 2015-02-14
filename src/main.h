#define BAUDRATE 38400
#define BUFFER_LENGTH 10
#define UBRR (((F_CPU / (BAUDRATE * 16UL))) - 1)

int main(void);
void sendUARTchar(char data);
void sendSPIchar(char data);