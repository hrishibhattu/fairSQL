#include<bits/stdc++.h>

using namespace std;

class InputBuffer {
public:
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;

    InputBuffer() {
        buffer = NULL;
        buffer_length = 0;
        input_length = 0;
    }

    InputBuffer* new_input_buffer();
    void print_prompt();
    void read_input(InputBuffer*);
    void close_input_buffer(InputBuffer*);

};

void InputBuffer::print_prompt() { printf("db > "); }

void InputBuffer::read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void InputBuffer::close_input_buffer(InputBuffer* input_buffer) {
    delete(input_buffer->buffer);
    delete(input_buffer);
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new InputBuffer();

    while(true) {
        input_buffer->print_prompt();
        input_buffer->read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0) {
            input_buffer->close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognised command '%s'.\n", input_buffer->buffer);
        }
    }
}
