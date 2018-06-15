//Barath Tirumala


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ID_LEN 11
#define MAX_NUM_LEN 5


int isReservedWord( char* s );


int isSpecialSymbol( char c );


int detectError( char *s );


int isOtherValid( char *s );


int main( void ){

    int i;
    int tempTokCtr = 0;

    char buffer[ 10000 ];
    char temp[ 10000 ];

    char sp[50]; //Name of input file
    printf( "What is the file name for your source program?\n" );
    scanf( "%s", sp );


    FILE *fin = fopen( sp, "r" );

    FILE *temp_fout = fopen( "temp_output.txt", "w" );

    while( fscanf( fin, "%s", buffer ) != EOF ){

        int len = (int) strlen( buffer ); //Length of read-in token.

        //For the length of the read-in token:
        for( i = 0; i < len; i++ ){

            if( i == len-1 && !isSpecialSymbol( buffer[ i ] ) ){
                fprintf( temp_fout, "%s ", buffer );
                tempTokCtr++; //Increment the token counter.
            }

            //If the i-th element of the token is a special symbol.
            else if( isSpecialSymbol( buffer[ i ] ) ){

                if( len > 1 ){
                    if( buffer[ i ] == '/' && buffer[ i+1 ] == '*' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "/* " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( buffer[ i ] == '*' && buffer[ i+1 ] == '/' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "*/ " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( buffer[ i ] == '!' && buffer[ i+1 ] == '=' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "!= " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( buffer[ i ] == '<' && buffer[ i+1 ] == '=' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "<= " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( buffer[ i ] == '>' && buffer[ i+1 ] == '=' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, ">= " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( buffer[ i ] == ':' && buffer[ i+1 ] == '=' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, ":= " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+2, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( len > 3 && buffer[ i ] == 'n' && buffer[ i+1 ] == 'u' && buffer[ i+2 ] == 'l' && buffer[ i+3 ] =='l' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "null " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+4, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }
                    else if( len > 2 && buffer[ i ] == 'o' && buffer[ i+1 ] == 'd' && buffer[ i+2 ] == 'd' ){
                        strncpy( temp, buffer, i );
                        temp[ i ] = '\0';

                        fprintf( temp_fout, "%s ", temp );
                        tempTokCtr++;

                        fprintf( temp_fout, "odd " );
                        tempTokCtr++;

                        strncpy( buffer, &buffer[i]+3, len-1 );
                        buffer[ len - 1 ] = '\0';
                        len = (int) strlen( buffer );
                        i = -1;
                    }

                }

                //Special symbol token at the beginning.
                if( i == 0 ){
                    //Print symbol as individual token.
                    fprintf( temp_fout, "%c ", buffer[i] );
                    tempTokCtr++; //Increment token counter.

                    strncpy( buffer, &buffer[i]+1, len-1 );
                    buffer[ len - 1 ] = '\0';
                    len = (int) strlen( buffer );
                    i = -1;
                }

                if( i > 0 ){
                    strncpy( temp, buffer, i );
                    temp[ i ] = '\0';

                    fprintf( temp_fout, "%s ", temp );
                    tempTokCtr++;

                    fprintf( temp_fout, "%c ", buffer[i] );
                    tempTokCtr++;

                    strncpy( buffer, &buffer[i]+1, len-1 );
                    buffer[ len - 1 ] = '\0';
                    len = (int) strlen( buffer );
                    i = -1;
                }

            }

        }

    }
    fclose( temp_fout );
    fclose( fin );

    fin = fopen( "temp_output.txt", "r" );
    FILE *table = fopen( "lexeme_table.txt", "w" ); //Will hold the lexeme table.
    FILE *list = fopen( "lexeme_list.txt", "w" ); //Will hold the lexeme list.

    //Print header for lexeme table.
    fprintf( table, "Lexeme Table:\n%15s%15s\n", "lexeme", "token type");


    //Initialize.
    int isResWord = -1;
    int len = 0;
    int isComment = 0;

    //For the length of tokens.
    while( fscanf( fin, "%s ", buffer ) != EOF ){

        len = (int) strlen( buffer ); //Get token string length.

        //Recognize beginning of comment block.
        if( !strcmp( buffer, "/*" ) ){
            isComment = 1;
        }

        //Recognize end of comment block.
        else if( isComment == 1 && !strcmp( buffer, "*/" ) ){
            isComment = 0;
        }

        else if( !isComment ){

            //Error detection by token.
            if( detectError( buffer ) ){
                fclose( fin );
                fclose( table );
                fclose( list );
                exit( 0 );
            }

            isResWord = isReservedWord( buffer );

            if( isResWord != -1 ){

                fprintf( table, "%15s%15d\n", buffer, isResWord );
                fprintf( list, "%d ", isResWord );

            }

            else if( isalpha( buffer[0] ) ){

                fprintf( table, "%15s%15d\n", buffer, 2 );
                fprintf( list, "2 %s ", buffer );

            }


            else if( isdigit( buffer[0] ) ){

                fprintf( table, "%15s%15d\n", buffer, 3 );
                fprintf( list, "3 %s ", buffer );

            }


            else{

                fprintf( table, "%15s%15d\n", buffer, isOtherValid( buffer ) );
                fprintf( list, "%d ", isOtherValid( buffer ) );

            }
        }


    }

    fclose( fin );

    char c;
    // Read contents from file
    c = fgetc(table);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(table);
    }

    c = fgetc(list);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(list);
    }


    fclose( table );
    fclose( list );

    fin = fopen( sp, "r" );
    FILE *source = fopen( "source_program.txt", "w" );
    char copy;

    while( ( copy = fgetc( fin ) ) != EOF )
        fputc( copy, source );
    fclose( fin );
    fclose( source );
    remove( "temp_output.txt" );



    return 0;

}


int detectError( char *s ){

    int i;
    int len = (int) strlen( s );


    if( len == 1 && s[0] == ':' ){
        printf( "Error: Invalid Symbol: :\n" );
        return 1;
    }

    //Check for invalid symbol.
    for( i = 0; i < len; i++ ){

        if( !isalnum(s[i]) && !isSpecialSymbol( s[i] ) ){
            printf( "Error: Invalid Symbol: %c\n", s[i] );
            return 1;
        }
    }


    if( len > 1 ){


        if( isalpha( s[0] ) ){
            for( i = 1; i < len; i++ ){
                if( i > MAX_ID_LEN ){
                    printf( "Error: Variable name: %s is too long.\n", s );
                    return 1;
                }
            }
        }

        if( isdigit( s[0] ) ){


            for( i = 1; i < len; i++ ){

                if( isalpha( s[i] ) ){
                    printf( "Error: Variable name: %s begins with a number.\n", s );
                    return 1;
                }

            }

            if( i > MAX_NUM_LEN ){
                printf( "Error: Number %s is too long.\n", s );
                return 1;
            }

        }

    }

    return 0;

}

int isSpecialSymbol( char c ){

    if( c == '+' )
        return 1;
    else if( c == '-' )
        return 1;
    else if( c == '*' )
        return 1;
    else if( c == '/' )
        return 1;
    else if( c == '(' )
        return 1;
    else if( c == ')' )
        return 1;
    else if( c == '=' )
        return 1;
    else if( c == ',' )
        return 1;
    else if( c == '.' )
        return 1;
    else if( c == '<' )
        return 1;
    else if( c == '>' )
        return 1;
    else if( c == ';' )
        return 1;
    else if( c == ':' )
        return 1;

    return 0;

}


int isReservedWord( char* s ){

    if( !strcmp( s, "const" ) )
        return 28;
    else if( !strcmp( s, "int" ) )
        return 29;
    else if( !strcmp( s, "procedure" ) )
        return 30;
    else if( !strcmp( s, "call" ) )
        return 27;
    else if( !strcmp( s, "begin" ) )
        return 21;
    else if( !strcmp( s, "end" ) )
        return 22;
    else if( !strcmp( s, "if" ) )
        return 23;
    else if( !strcmp( s, "then" ) )
        return 24;
    else if( !strcmp( s, "else" ) )
        return 33;
    else if( !strcmp( s, "while" ) )
        return 25;
    else if( !strcmp( s, "var" ) )
        return 29;
    else if( !strcmp( s, "do" ) )
        return 26;
    else if( !strcmp( s, "read" ) )
        return 32;
    else if( !strcmp( s, "write" ) )
        return 31;

    return -1;

}

int isOtherValid( char *s ){

    if( !strcmp( s, "null" ) )
        return 1;
    else if( !strcmp( s, "+" ) )
        return 4;
    else if( !strcmp( s, "-" ) )
        return 5;
    else if( !strcmp( s, "*" ) )
        return 6;
    else if( !strcmp( s, "/" ) )
        return 7;
    else if( !strcmp( s, "<=" ) )
        return 12;
    else if( !strcmp( s, ">=" ) )
        return 14;
    else if( !strcmp( s, "(" ) )
        return 15;
    else if( !strcmp( s, ")" ) )
        return 16;
    else if( !strcmp( s, "," ) )
        return 17;
    else if( !strcmp( s, ";" ) )
        return 18;
    else if( !strcmp( s, "." ) )
        return 19;
    else if( !strcmp( s, ":=" ) )
        return 20;
    else if( !strcmp( s, "odd" ) )
        return 8;
    else if( !strcmp( s, "=" ) )
        return 9;
    else if( !strcmp( s, "!=" ) )
        return 10;
    else if( !strcmp( s, "<" ) )
        return 11;
    else if( !strcmp( s, ">" ) )
        return 13;

}
