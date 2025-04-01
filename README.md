# minitalk - 42 School

### 🏆 Score: **125/100** (+25 for bonus)

## 📚 About the Project

**minitalk** is a client-server communication project that demonstrates basic inter-process communication using signals. The goal is to create a small client-server program where the client sends a message to the server one character at a time, using Unix signals, and the server prints out the received message

### 🧠 My Approach

1. **Using Signals**: The client and server communicate using Unix signals, specifically `SIGUSR1` and `SIGUSR2`, where each signal represents a single bit of data.
2. **Encoding the Message**: The client first sends the length of the message, followed by each character. Each character is converted into its binary form and transmitted bit by bit using signals.
3. **Server Handling**: The server first listens for the message length, then allocates the necessary space. It then receives and decodes each signal to store the characters, and finally, prints the complete message.

### 📚 What I Learned
- **Signal Handling**: Working with Unix signals for inter-process communication
- **Bitwise Manipulation**: Encoding and decoding messages by manipulating individual bits
- **Synchronization**: Ensuring that both the client and server are synchronized when transmitting and receiving messages

## 🚀 Usage

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/your-username/minitalk.git
cd minitalk
```

### 2️⃣ Compile the Program
```bash
make
```

### 3️⃣ Run the Server

```bash
./server
```

The server will start and wait for the client to send a message

### 4️⃣ Run the Client (in different terminal)

```bash
./client <server_pid> "Hello, World!"
```

Where `<server_pid>` is the Process ID of the server (server printed it after starting)

### 5️⃣ Test with Multiple Messages

You can send different messages to the server, and it will decode and print each one

```bash
./client <server_pid> "This is a test message"
```

## 🏁 Conclusion

**minitalk** demonstrates how to use Unix signals for basic communication between a client and server. It provides an introduction to signal handling and inter-process communication
