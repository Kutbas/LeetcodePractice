from collections import deque, defaultdict


class Solution:
    def __init__(self):
        self.m = 0
        self.n = 0
        self.vis = []
        self.dx = [0, 0, 1, -1]
        self.dy = [1, -1, 0, 0]

    def numIslands(self, grid):
        self.m, self.n = len(grid), len(grid[0])
        self.vis = [[False] * self.n for _ in range(self.m)]
        ret = 0

        for i in range(self.m):
            for j in range(self.n):
                if not self.vis[i][j] and grid[i][j] == "1":
                    ret += 1
                    self.bfs(grid, i, j)

        return ret

    def bfs(self, grid, i, j):
        q = deque()
        q.append((i, j))
        self.vis[i][j] = True

        while q:
            a, b = q.popleft()
            for k in range(4):
                x = a + self.dx[k]
                y = b + self.dy[k]
                if (
                    0 <= x < self.m
                    and 0 <= y < self.n
                    and not self.vis[x][y]
                    and grid[x][y] == "1"
                ):
                    q.append((x, y))
                    self.vis[x][y] = True

    def nearestExit(self, maze, entrance):
        m, n = len(maze), len(maze[0])
        vis = [[False for _ in range(n)] for _ in range(m)]
        dx = [0, 0, 1, -1]
        dy = [1, -1, 0, 0]

        q = deque()
        q.append((entrance[0], entrance[1]))
        vis[entrance[0]][entrance[1]] = True
        steps = 0

        while q:
            steps += 1

            for _ in range(q):
                a, b = q.popleft()
                for k in range(4):
                    x, y = a + dx[k], b + dy[k]
                    if (
                        0 <= x < m
                        and 0 <= y < n
                        and not vis[x][y]
                        and maze[x][y] == "."
                    ):
                        if x == 0 or x == m - 1 or y == 0 or y == n - 1:
                            return steps
                        q.append((x, y))
                        vis[x][y] = True
        return -1

    def canFinish(self, n, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        edges = defaultdict(list)
        in_degree = [0] * n

        for a, b in prerequisites:
            edges[b].append(a)
            in_degree[a] += 1

        q = deque([i for i in range(n) if in_degree[i] == 0])

        while q:
            t = q.popleft()
            for a in edges[t]:
                in_degree[a] -= 1
                if in_degree[a] == 0:
                    q.append(a)

        return all(degree == 0 for degree in in_degree)

    def solve(self, board):
        self.m, self.n = len(board), len(board[0])
        self.vis = [[False] * self.n for _ in range(self.m)]
        self.dx = [0, 0, 1, -1]
        self.dy = [1, -1, 0, 0]

        for i in range(self.m):
            if board[i][0] == "O":
                self.bfs(board, i, 0)
            if board[i][self.n - 1] == "O":
                self.bfs(board, i, self.n - 1)

        for i in range(self.n):
            if board[0][i] == "O":
                self.bfs(board, 0, i)
            if board[self.m - 1][i] == "O":
                self.bfs(board, self.m - 1, i)

        for i in range(self.m):
            for j in range(self.n):
                if board[i][j] == "O":
                    board[i][j] = "X"
                elif board[i][j] == ".":
                    board[i][j] = "O"

    def bfs(self, board, i, j):
        q = deque()
        q.append((i, j))
        board[i][j] = "."
        self.vis[i][j] = True

        while q:
            a, b = q.popleft()
            for k in range(4):
                x, y = a + self.dx[k], b + self.dy[k]
                if (
                    0 <= x < self.m
                    and 0 <= y < self.n
                    and not self.vis[x][y]
                    and board[x][y] == "O"
                ):
                    q.append((x, y))
                    board[x][y] = "."
                    self.vis[x][y] = True
