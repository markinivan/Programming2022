#include<locale.h>;
#include<stdio.h>;
struct product {
	char* name[20];
	int article;
};
int main() {
	setlocale(LC_ALL, "rus");
	int ident, id, size=100;
	struct product selected;
	struct product* storage;
	storage = (struct product*)malloc(size*sizeof(struct product));
	printf("�������� - 0, ���������� - 1\n����: ");
	scanf_s("%d", &ident);
	if (ident == 0) {
		while (1) {
			printf("���� ��������\n1.�������� ����� �� �����\n2.������� �����\n3.������� ����� �� ������\n����:");
			scanf_s("%d", &id);
			switch (id)
			{
			case 1:
				printf("������� �������� ������:");
				scanf_s("%s", &selected.name);
				printf("������� ������� ������:");
				scanf_s("%d",&selected.article);
				printf("%s %d",selected.name, selected.article);
				break;
			default:
				break;
			}

		}
	}

	return 0;
	system("pause");
}