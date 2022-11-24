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
	printf("Продавец - 0, покупатель - 1\nВвод: ");
	scanf_s("%d", &ident);
	if (ident == 0) {
		while (1) {
			printf("Меню продавца\n1.Добавить товар на склад\n2.Изменть товар\n3.Удалить товар со склада\nВвод:");
			scanf_s("%d", &id);
			switch (id)
			{
			case 1:
				printf("Введите название товара:");
				scanf_s("%s", &selected.name);
				printf("Введите артикул товара:");
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