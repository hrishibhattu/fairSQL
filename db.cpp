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

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

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

class Statement {
public:
    StatementType type;
    PrepareResult prepare_statement(InputBuffer* input, Statement* statement) {
        if(strncmp(input->buffer, "insert", 6) == 0) {
            statement->type = STATEMENT_INSERT;
            return PREPARE_SUCCESS;
        }
        if(strcmp(input->buffer, "select") == 0) {
            statement->type = STATEMENT_SELECT;
            return PREPARE_SUCCESS;
        }

        return PREPARE_UNRECOGNIZED_STATEMENT;
    }
};

class CommandProcessor {
private:
    MetaCommandResult do_meta_command(InputBuffer* input) {
        if(strcmp(input->buffer, ".exit") == 0) exit(EXIT_SUCCESS);
        else return META_COMMAND_UNRECOGNIZED_COMMAND;
    }

    void execute_statement(Statement* statement) {
        switch(statement->type) {
            case (STATEMENT_INSERT):
                printf("Insert statement\n");
                break;
            case (STATEMENT_SELECT):
                printf("Select statement\n");
                break;
        }
    }
public:
    void process(InputBuffer* &input) {
        if(input->buffer[0] == '.') {
            switch(do_meta_command(input)) {
                case (META_COMMAND_SUCCESS):
                    break;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input->buffer);
                    break;
            }
        }

        Statement statement;
        switch(statement.prepare_statement(input, &statement)) {
            case (PREPARE_SUCCESS): break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at the start of '%s'\n", input->buffer);
                break;
        }

        execute_statement(&statement);
        printf("Executed\n");
    }
};


int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new InputBuffer();
    CommandProcessor processor;
    while(true) {
        input_buffer->print_prompt();
        input_buffer->read_input(input_buffer);
        processor.process(input_buffer);
    }
}
