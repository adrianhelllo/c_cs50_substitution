#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_len(string key);
int check_repeated(string key);
int check_alphabetic(string key);
int is_ltr_wrong(char ltr);
string ask_plaintext();
string generate_cipher(string pl_text, string key);

int KEY_LENGTH = 26;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];

    if (check_len(key) == 1)
    {
        printf("Key must contain %i characters.\n", KEY_LENGTH);
        return 1;
    }

    if (check_repeated(key) == 1)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    if (check_alphabetic(key) == 1)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        key[i] = tolower(key[i]);
    }

    string plain_text = ask_plaintext();
    printf("ciphertext: %s\n", generate_cipher(plain_text, key));
}

int check_len(string key)
{
    int len = strlen(key);

    if (len != KEY_LENGTH)
    {
        return 1;
    }

    return 0;
}

int check_repeated(string key)
{
    char chars_seen[KEY_LENGTH];
    int seen_size = 0;

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        char cur = tolower(key[i]);
        for (int seen = 0; seen < seen_size; seen++)
        {
            if (chars_seen[seen] == cur)
            {
                return 1;
            }
        }

        chars_seen[seen_size] = cur;
        seen_size++;
    }

    return 0;
}

int is_ltr_wrong(char ltr)
{
    if (isalpha(ltr) == 0)
    {
        return 1;
    }

    return 0;
}

int check_alphabetic(string key)
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (is_ltr_wrong(key[i]) == 1)
        {
            return 1;
        }
    }

    return 0;
}

string ask_plaintext()
{
    string pl_text;

    do
    {
        pl_text = get_string("plaintext: ");
    }
    while (strlen(pl_text) < 1);

    return pl_text;
}

string generate_cipher(string pl_text, string key)
{
    int len = strlen(pl_text);

    for (int i = 0; i < len; i++)
    {
        char cur_ltr = pl_text[i];

        if (!is_ltr_wrong(cur_ltr))
        {
            int ltr_index = tolower(cur_ltr) - 'a';
            char new_char = key[ltr_index];

            if (isupper(pl_text[i]))
            {
                new_char = toupper(new_char);
            }

            pl_text[i] = new_char;
        }
    }

    return pl_text;
}
