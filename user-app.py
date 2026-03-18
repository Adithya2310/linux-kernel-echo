def main():
    # 1. Take input from the user
    user_input = input("Enter a message to send to the kernel: ")

    # 2. Write the input to the kernel space
    # We open the file in write mode ('w'). Writing to this file descriptor 
    # triggers the `custom_write` function in your kernel module.
    with open('/proc/kernel_driver', 'w') as driver_write_handle:
        driver_write_handle.write(user_input)
        print(f"[*] Successfully wrote to kernel: '{user_input}'")

    # 3. Read the output back from the kernel space
    # We open the file in read mode ('r'). Reading from this file descriptor 
    # triggers the `custom_read` function in your kernel module.
    with open('/proc/kernel_driver', 'r') as driver_read_handle:
        message_from_kernel_space = driver_read_handle.read()
        print(f"[*] Response from kernel space: '{message_from_kernel_space.strip()}'")

if __name__ == "__main__":
    main()