#include <iostream>

int main()
{
    //удалить из исходной строки все пробельные символы, пробегая строку справа налево
    const int bufferSize = 100;
    int len = 0;
    char helperString[bufferSize];
    char reversedString[bufferSize];
    char result[bufferSize];
    char format[] = "%s";
    char charToDelete = ' ';
    
    //gets(s);
    __asm {
        //gets

        mov eax, bufferSize
        push eax
        lea eax, helperString
        push eax
        call gets_s
        add esp, 8 

        //printf
        lea eax, helperString
        push eax
        lea eax, format
        push eax
        call printf_s
        add esp, 8

        lea ebx, helperString //кладем исходную строку в ebx
        mov ecx, len //кладем длинну строки в счетчик индексов (для прохода исходной строки справа налево)
        mov edi, 0

        cmp byte ptr[ebx][0], 0
        je FIN

        LEN_FINDER : //цикл для подсчета элементов в исходной строке
        inc ecx //+1 к счетчику по элементам
            mov ah, [ebx][ecx] //кладем символ в ah
            inc edi //+1 к длинне

            cmp ah, 0 //проверяем на конец строки
            jne LEN_FINDER //если не конец, то идем снова в цикл

            sub ecx, 1 //игнорируем элемент "0", т.е. после последнего
            mov esi, 0 //инициализируем счетчик по позициям в результате
            lea edx, reversedString //кладем пустую строку в edx
            mov ah, charToDelete //кладем в ah символ, который хотим удалить в исходной строке

            CYCLE : //берёт кол-во итераций из ecx
        mov al, [ebx][ecx] //кладем символ

            cmp ah, al //проверяем равен ли символ пробелу
            je LOOP1 //если да, игнорируем его и переходим к следющему символу

            mov[edx][esi], al //символ не пробел, значит пишем его в результат
            add esi, 1 //счетчик + 1

            LOOP1:

        loop CYCLE

            //проделываем то же, что и в цикле, но для символа в позиции 0
            mov al, [ebx][ecx]
            cmp ah, al
            je NEXT
            mov[edx][esi], al
            add esi, 1

            NEXT :
        mov byte ptr[edx][esi], 0

            //далее реверсируем строку
            mov ecx, 0 //инициализируем счётчик по элементам
            lea eax, result //кладем пустую строку в eax
            mov byte ptr[eax][0], 0 

            cmp BYTE PTR[edx][0], 0
            je END
            LEN_FINDER2 : //цикл для подсчета элементов в новой строке
        inc ecx //+1 к счетчику по элементам
            mov ah, [edx][ecx] //кладем символ в ah
            cmp byte ptr[edx][ecx], 0 //проверяем на конец строки
            jne LEN_FINDER2 //если не конец, то идем снова в цикл

            sub ecx, 1 //игнорируем элемент "0", т.е. после последнего
            mov esi, 0 //инициализируем счетчик по позициям в результате
            lea eax, result //кладем пустую строку в eax

            REVERSE :
        mov bl, [edx][ecx] //кладем символ
            mov[eax][esi], bl
            add esi, 1 //счетчик + 1
            loop REVERSE

            //проделываем то же, что и в цикле, но для символа в позиции 0
            mov bl, [edx][ecx]
            mov[eax][esi], bl
            add esi, 1

            cmp byte ptr[eax][0], 0
            je END
            mov byte ptr[eax][esi], 0

            END :
        lea eax, result
            push eax
            lea eax, format
            push eax
            call printf_s
            add esp, 8
            jmp FIN2

            FIN :
        lea eax, result
            mov byte ptr[result][0], 0
            lea eax, reversedString
            mov byte ptr[reversedString][0], 0

            FIN2 :
    }
    std::cout << std::endl;
    std::cout << "Pre result: " << reversedString << std::endl;
    std::cout << "Result:" << result << std::endl;
    return 0;
}