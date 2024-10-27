#include <iostream>
#include <fstream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <cstring>

using namespace std;

// Define message structure
struct msg_buffer {
    long mtype;
    char mtext[100];
};

int Home = 1;
int Setting = 2;

int main() {
    // Generate key for message queue
    key_t key = ftok("message_queue.txt", 65);

    // Create message queue
    int msgid = msgget(key, 0666 | IPC_CREAT); // permission 666 is read and write
    if (msgid == -1) // -1 means the message queue is not created  
    {  
        cout << "Error in creating queue\n";  
        exit(0);  
    }  

    // Input message to be sent
    string message;
    cout << "Enter message: ";
    getline(cin, message);

    // Prepare message buffer

    // Send message to queue
    // if (msgsnd(msgid, &buffer, sizeof(buffer.mtext), 0) == -1)
    // {
    //     cout << "Message can not sent!" << endl;
    // }
    // else 
    // {
    //     cout << "Message sent!" << endl;
    // }

    for (int i = 1; i < 3; ++i)
    {
        struct msg_buffer buffer;
        buffer.mtype = i;
        strcpy(buffer.mtext, message.c_str());
        if (msgsnd(msgid, &buffer, sizeof(buffer.mtext), 0) == -1)
        {
            cout << "Message can not sent!" << endl;
        }
        else 
        {
            cout << "Message sent!" << endl;
        }
    }

    return 0;
}