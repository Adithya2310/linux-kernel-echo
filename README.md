# Simple Kernel-User Space Communication

This project demonstrates a basic way to send data back and forth between user space (a Python app) and the Linux kernel space using the `/proc` filesystem.

## What's inside

- **`ldd.c`**: This is the kernel module. When loaded, it creates a virtual file at `/proc/kernel_driver`. It acts as a bridge, storing whatever you write to it in a temporary kernel buffer, and giving it back to you when you read from it.
- **`user-app.py`**: A simple Python script that takes your input, writes it to our custom `/proc` file (sending it to the kernel), and then reads it right back out to prove the data actually travelled to the kernel and back.
- **`Makefile`**: Builds the kernel module.

## How to use it

1. **Build the kernel module**:
   ```bash
   make
   ```

2. **Load the module into the kernel**:
   ```bash
   sudo insmod ldd.ko
   ```

3. **Run the Python app**:
   ```bash
   python3 user-app.py
   ```
   *It will prompt you to enter a message. Type something and hit enter. You should see it successfully write to and read from the kernel.*

4. **Verify in the kernel logs** (Optional):
   ```bash
   sudo dmesg | tail
   ```
   *You'll see the kernel's `printk` logs verifying it actually received and read your message on the backend.*

5. **Clean up**:
   ```bash
   sudo rmmod ldd
   make clean
   ```
