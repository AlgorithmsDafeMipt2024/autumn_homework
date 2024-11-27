#include <bits/stdc++.h>

using namespace std;

class NegativeCycleGraph : public std::logic_error {
  using std::logic_error::logic_error;
};

struct Edge {
  int from, to, weight;  // Представляет ребро графа с начальной и конечной
                         // вершинами и весом.
};

struct Graph {
  vector<Edge> edges;  // Этот вектор нужен в реализации алгоритма Беллмана
                       // форда
  vector<vector<int>> gr;  // Список смежности для невзвешенного графа.
  vector<vector<pair<int, int>>>
      directed_graph;  // Список смежности для взвешенного ориентированного
                       // графа.
  vector<int> used;  // Массив для отслеживания посещенных вершин.
  vector<int> color;  // Массив для отслеживания состояния вершин (0 - не
                      // посещена, 1 - в процессе, 2 - посещена).
  vector<int> parents;  // Массив для хранения родителей вершин в дереве обхода.
  vector<int>
      topsort;  // Массив для хранения порядка топологической сортировки.
  vector<vector<int>> comps;  // Массив для хранения компонент связности.
  vector<int> dist;  // Массив для хранения расстояний от начальной вершины.
  int cnt = 0;       // Счетчик компонент связности.

  void ReadWUG(int& n, int& m, vector<vector<int>>& vec) {
    // Читает взвешенный неориентированный граф из вектора vec.
    directed_graph.resize(n + 1);  // Инициализация списка смежности.
    used.resize(n + 1, 0);  // Инициализация массива посещенных вершин.
    color.resize(n + 1, 0);  // Инициализация массива цветов.
    parents.resize(n + 1, -1);  // Инициализация массива родителей.
    comps.resize(n + 1);  // Инициализация массива компонент.
    for (int i = 0; i < m; i++) {
      int u, v, w;  // Начальная, конечная вершины и вес ребра.
      u = vec[i][0];
      v = vec[i][1];
      w = vec[i][2];
      directed_graph[u].push_back(
          {v, w});  // Добавление ребра в список смежности.
      directed_graph[v].push_back({u, w});  // Добавление обратного ребра.
    }
  }

  void ReadWDG(int& n, int& m, vector<vector<int>>& vec) {
    // Читает взвешенный ориентированный граф из вектора vec.
    directed_graph.resize(n + 1);
    used.resize(n + 1, 0);
    color.resize(n + 1, 0);
    parents.resize(n + 1, -1);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      u = vec[i][0];
      v = vec[i][1];
      w = vec[i][2];
      directed_graph[u].push_back(
          {v, w});  // Добавление ребра в список смежности.
    }
  }

  void ReadUUG(int& n, int& m, vector<pair<int, int>>& vec) {
    // Читает невзвешенный неориентированный граф из вектора vec.
    gr.resize(n + 1);
    used.resize(n + 1, 0);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      u = vec[i].first;
      v = vec[i].second;
      gr[u].push_back(v);  // Добавление ребра в список смежности.
      gr[v].push_back(u);  // Добавление обратного ребра.
    }
  }

  void ReadUDG(int& n, int& m, vector<pair<int, int>>& vec) {
    // Читает невзвешенный ориентированный граф из вектора vec.
    gr.resize(n + 1);
    used.resize(n + 1, 0);
    color.resize(n + 1, 0);
    parents.resize(n + 1, -1);
    comps.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      u = vec[i].first;
      v = vec[i].second;
      gr[u].push_back(v);  // Добавление ребра в список смежности.
    }
  }

  void Dfs(int u, int count) {
    // Выполняет обход в глубину (DFS) от вершины u и сохраняет компоненты
    // связности.
    used[u] = 1;  // Помечаем вершину как посещенную.
    comps[count].push_back(u);  // Добавляем вершину в текущую компоненту.
    for (auto it : gr[u]) {
      if (!used[it]) {
        Dfs(it, count);  // Рекурсивный вызов для соседней вершины.
      }
    }
    topsort.push_back(
        u);  // Добавляем вершину в порядок топологической сортировки.
  }

  vector<vector<int>> components(int& n) {
    // Находит все компоненты связности в графе.
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        Dfs(i, cnt++);  // Запускаем DFS для каждой непосещенной вершины.
      }
    }
    return comps;  // Возвращаем найденные компоненты.
  }

  bool HasCycleUndirected(int& n) {
    // Проверяет наличие циклов в невзвешенном неориентированном графе.
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        if (DfsCycleUndirected(i, -1)) {
          return true;  // Если цикл найден, возвращаем true.
        }
      }
    }
    return false;  // Циклов не найдено.
  }
  bool DfsCycleUndirected(int v, int p) {
    // Выполняет DFS для проверки наличия циклов в невзвешенном графе.
    used[v] = 1;  // Помечаем вершину как посещенную.
    for (int to : gr[v]) {
      if (!used[to]) {
        if (DfsCycleUndirected(to, v)) {
          return true;  // Если цикл найден, возвращаем true.
        };
      } else if (to != p) {
        return true;  // Если соседняя вершина уже посещена и не является
                      // родителем, найден цикл.
      }
    }
    return false;  // Циклов не найдено.
  }

  bool HasCycleDirected(int& n) {
    // Проверяет наличие циклов в взвешенном ориентированном графе.
    for (int i = 1; i <= n; i++) {
      if (!used[i]) {
        if (DfsCycleDirectedW(i)) {
          return true;  // Если цикл найден, возвращаем true.
        }
      }
    }
    return false;  // Циклов не найдено.
  }

  bool DfsCycleDirectedW(int v) {
    // Выполняет DFS для проверки наличия циклов в ориентированном графе.
    used[v] = 1;  // Помечаем вершину как посещенную.
    color[v] = 1;  // Устанавливаем цвет в процессе.
    for (auto& edge : directed_graph[v]) {
      int const to = edge.first;  // Получаем соседнюю вершину.
      if (!used[to]) {
        if (DfsCycleDirectedW(to)) {
          return true;  // Если цикл найден, возвращаем true.
        }
      } else if (color[to] == 1) {
        return true;  // Если соседняя вершина в процессе, найден цикл.
      }
    }
    color[v] = 2;  // Устанавливаем цвет завершенной.
    return false;  // Циклов не найдено.
  }

  // Используется для нахождения Top_Sort и проверке на циклы
  bool DfsCycleDirectedU(const int v) {
    // Выполняет DFS для топологической сортировки и проверки наличия циклов.
    used[v] = 1;  // Помечаем вершину как посещенную.
    color[v] = 1;  // Устанавливаем цвет в процессе.
    for (auto& edge : gr[v]) {
      int const to = edge;  // Получаем соседнюю вершину.
      if (!used[to]) {
        if (DfsCycleDirectedU(to)) {
          return true;  // Если цикл найден, возвращаем true.
        }
      } else if (color[to] == 1) {
        return true;  // Если соседняя вершина в процессе, найден цикл.
      }
    }
    color[v] = 2;  // Устанавливаем цвет завершенной.
    topsort.push_back(
        v);  // Добавляем вершину в порядок топологической сортировки.
    return false;  // Циклов не найдено.
  }

  // Реализация Алгоритма Флойда, на вход передается матрица (в виде двумерного
  // массива), возвращает массив пар, в которой содержится пара вершин между
  // которыми ориентированное ребро и его вес
  vector<pair<pair<int, int>, int>> AlgotihmFloida(int n,
                                                   vector<vector<int>>& vec) {
    // Тройной цикл для перебора всех пар вершин (i, j) с промежуточной вершиной
    // k
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          // Проверяем, что i и j не совпадают
          if (i != j) {
            // Обновляем расстояние между вершинами i и j, если найдено более
            // короткое
            vec[i][j] = min(vec[i][j], vec[i][k] + vec[k][j]);
          }
        }
      }
    }

    // Вектор для хранения результатов: пар (i, j) и их расстояний
    vector<pair<pair<int, int>, int>> ans;
    // Перебираем все пары вершин для формирования результата
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        // Проверяем, что расстояние не равно бесконечности и вершины i и j не
        // совпадают
        if (vec[i][j] != 1e9 && i != j) {
          // Добавляем пару (i, j) и соответствующее расстояние в ответ
          ans.push_back({{i, j}, vec[i][j]});
        }
      }
    }

    // Возвращаем вектор с кратчайшими путями
    return ans;
  }

  // Ниже реализован алгоритм Белмана Форда, который ищет кратчайшее расстояние
  // между вершиной s и всеми остальными
  vector<int> AlgorithmBellmanaF(int n, int m, int s) {
    edges.resize(m);  // Изменяем размер вектора рёбер на количество рёбер в графе
    int k = 0;  // Индекс для добавления рёбер

    // Заполнение списка рёбер
    for (int i = 1; i <= n; i++) {
      for (const auto& neighbor : directed_graph[i]) {
        edges[k].from = i;  // Устанавливаем начальную вершинуу
        edges[k].to = neighbor.first;  // Устанавливаем конечную вершину
        edges[k].weight = neighbor.second;  // Устанавливаем вес ребра
        k++;  // Переходим к следующему ребру
      }
    }

    vector<int> distance(
        n + 1, 1e9);  // Инициализация расстояний до всех вершин бесконечностью
    distance[s] = 0;  // Расстояние до стартовой вершины равно 0

    // Основной цикл алгоритма Беллмана-Форда
    for (int i = 1; i <= n - 1; i++) {  // Повторяем n-1 раз
      for (const auto& edge : edges) {  // Проходим по всем рёбрам
        if (distance[edge.from] !=
            1e9) {  // Если до начальной вершины есть путь
          distance[edge.to] =  // Обновляем расстояние до конечной вершины
              min(distance[edge.to],
                  distance[edge.from] +
                      edge.weight);  // Сравниваем текущее расстояние и новое
        }
      }
    }

    // Проверка на отрицательные циклы
    for (const auto& edge : edges) {  // Проходим по всем рёбрам еще раз
      if (distance[edge.from] != 1e9 &&  // Если до начальной вершины есть путь
          distance[edge.to] >
              distance[edge.from] +
                  edge.weight) {  // Если можно улучшить расстояние
        throw NegativeCycleGraph(
            "Error: Graph has negative cycle.");  // Генерация исключения при
                                                  // обнаружении отрицательного
                                                  // цикла
      }
    }
    return distance;  // Возвращаем массив расстояний до всех вершин
  }
};
