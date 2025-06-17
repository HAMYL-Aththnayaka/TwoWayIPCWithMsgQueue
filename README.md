# TwoWayIPCWithMsgQueue
A Example of IPC With MsgQueue with 2 messages 
ChatGPT said:
markdown
Copy
Edit
# Message Queue Example in C

This program demonstrates the use of System V message queues for inter-process communication (IPC) between a parent and child process.

---

## Description

- The program creates a message queue.
- The child process prompts the user to input two strings (First Name and Second Name).
- The child sends these two messages to the message queue with different message types (`1` and `2`).
- The parent process waits for the child to finish and then receives the two messages from the queue.
- After receiving, the parent prints both messages.
- Finally, the message queue is removed.

---

## How it works

The program creates a message queue using msgget.

It forks into a child and parent process.

The child reads two strings from the user, sends them as messages to the queue.

The parent waits for the child, then reads the two messages from the queue by their message types.

The parent prints the received messages.

The message queue is deleted using msgctl.

yaml
Copy
Edit

---

## Prerequisites

- GCC compiler on a Unix/Linux system
- System V IPC support in the OS

---

## How to Compile

```bash
gcc -o msg_queue_example msg_queue_example.c
How to Run
bash
Copy
Edit
./msg_queue_example
Sample Output
mathematica
Copy
Edit
 ```
## OutPut Sample
Please Enter the First Name: John

The First Message Is Sent

Please Enter the Second Name: Doe

The Second Message Is Sent

The First Message Is: John

The Second Message Is: Doe

Message Queue removed successfully
# Error Handling
If msgget fails, the program prints an error and exits.

If msgsnd or msgrcv fail, the program prints an error and exits.

If fork fails, the program prints an error and exits.

The newline character from fgets is preserved in the messages.

Notes
The message queue key is fixed (114) in this example.

Message types are used to differentiate between the two messages.

The program assumes proper user input for simplicity.

License
This is a simple educational example for learning IPC with message queues.

Copy
Edit
