#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;

// Define message structure
struct msg_buffer {
    long mtype;
    char mtext[100];
};

int main() {
    // Generate key for message queue
    key_t key = ftok("message_queue.txt", 65);

    // Create message queue
    int msgid = msgget(key, 0666 | IPC_CREAT); // permission 666 is read and write

    // Receive message from queue
    struct msg_buffer buffer;
    msgrcv(msgid, &buffer, sizeof(buffer.mtext), 1, 0);

    // Display the message
    cout << "Received message: " << buffer.mtext << endl;

    // Close the queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}