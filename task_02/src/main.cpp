int main() { return 0; }

//Неориентированный граф задан в виде списка соседей каждой вершины. Два
//основных вопроса, на которые отвечает программа: удаление какой вершины/ребра
//сделает граф несвязным. Программа рассматривает случаи удаления каждого ребра
//и возможность дойти из одной вершины этого ребра до второй другим путем. В
//случае не нахождения такого пути, ребро считается слабым местом сети. Подобным
//образом проводится и проверка каждой вершины