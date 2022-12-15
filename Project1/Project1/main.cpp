#include <iostream>

int main()
{
    //������� �� �������� ������ ��� ���������� �������, �������� ������ ������ ������
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

        lea ebx, helperString //������ �������� ������ � ebx
        mov ecx, len //������ ������ ������ � ������� �������� (��� ������� �������� ������ ������ ������)
        mov edi, 0

        cmp byte ptr[ebx][0], 0
        je FIN

        LEN_FINDER : //���� ��� �������� ��������� � �������� ������
        inc ecx //+1 � �������� �� ���������
            mov ah, [ebx][ecx] //������ ������ � ah
            inc edi //+1 � ������

            cmp ah, 0 //��������� �� ����� ������
            jne LEN_FINDER //���� �� �����, �� ���� ����� � ����

            sub ecx, 1 //���������� ������� "0", �.�. ����� ����������
            mov esi, 0 //�������������� ������� �� �������� � ����������
            lea edx, reversedString //������ ������ ������ � edx
            mov ah, charToDelete //������ � ah ������, ������� ����� ������� � �������� ������

            CYCLE : //���� ���-�� �������� �� ecx
        mov al, [ebx][ecx] //������ ������

            cmp ah, al //��������� ����� �� ������ �������
            je LOOP1 //���� ��, ���������� ��� � ��������� � ��������� �������

            mov[edx][esi], al //������ �� ������, ������ ����� ��� � ���������
            add esi, 1 //������� + 1

            LOOP1:

        loop CYCLE

            //����������� �� ��, ��� � � �����, �� ��� ������� � ������� 0
            mov al, [ebx][ecx]
            cmp ah, al
            je NEXT
            mov[edx][esi], al
            add esi, 1

            NEXT :
        mov byte ptr[edx][esi], 0

            //����� ����������� ������
            mov ecx, 0 //�������������� ������� �� ���������
            lea eax, result //������ ������ ������ � eax
            mov byte ptr[eax][0], 0 

            cmp BYTE PTR[edx][0], 0
            je END
            LEN_FINDER2 : //���� ��� �������� ��������� � ����� ������
        inc ecx //+1 � �������� �� ���������
            mov ah, [edx][ecx] //������ ������ � ah
            cmp byte ptr[edx][ecx], 0 //��������� �� ����� ������
            jne LEN_FINDER2 //���� �� �����, �� ���� ����� � ����

            sub ecx, 1 //���������� ������� "0", �.�. ����� ����������
            mov esi, 0 //�������������� ������� �� �������� � ����������
            lea eax, result //������ ������ ������ � eax

            REVERSE :
        mov bl, [edx][ecx] //������ ������
            mov[eax][esi], bl
            add esi, 1 //������� + 1
            loop REVERSE

            //����������� �� ��, ��� � � �����, �� ��� ������� � ������� 0
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