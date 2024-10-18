import tkinter as tk
import tkinter.messagebox as messagebox

class LightsOutSolver:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.grid = [[0 for _ in range(cols)] for _ in range(rows)]

    def special_vectors(self, ri, ci):
        rxc = self.rows * self.cols
        temp = [0] * rxc
        temp[ri * self.cols + ci] = 1

        if ci + 1 < self.cols:
            temp[ri * self.cols + ci + 1] = 1
        if ci - 1 >= 0:
            temp[ri * self.cols + ci - 1] = 1
        if ri + 1 < self.rows:
            temp[(ri + 1) * self.cols + ci] = 1
        if ri - 1 >= 0:
            temp[(ri - 1) * self.cols + ci] = 1

        return temp

    def echelon(self, arr):
        row = len(arr)
        col = len(arr[0])
        for lead in range(row):
            if arr[lead][lead] == 0:
                for i in range(lead + 1, row):
                    if arr[i][lead] != 0:
                        self.rowswap(arr, lead, i)
                        break
            for i in range(lead + 1, row):
                if arr[i][lead] != 0:
                    self.rowdef(arr, lead, i)
        
        
        for i in range(row):
            if all(arr[i][j] == 0 for j in range(col - 1)) and arr[i][-1] != 0:
                return False  
        return True  

    def rowswap(self, arr, row1, row2):
        arr[row1], arr[row2] = arr[row2], arr[row1]

    def rowdef(self, arr, lead, row):
        col = len(arr[0])
        for i in range(col):
            arr[row][i] = (arr[lead][i] + arr[row][i]) % 2

    def solve(self, total_matrix, light_grid):
        rxc = self.rows * self.cols
        augmented_matrix = [[0 for _ in range(rxc + 1)] for _ in range(rxc)]

        for i in range(rxc):
            for j in range(rxc + 1):
                if j == rxc:
                    augmented_matrix[i][j] = light_grid[i // self.cols][i % self.cols]
                else:
                    augmented_matrix[i][j] = total_matrix[i][j]

        
        if not self.echelon(augmented_matrix):
            return None  

        var = [0] * rxc
        num = rxc - 1
        for i in range(rxc - 1, -1, -1):
            if augmented_matrix[i][i] == 0:
                var[num] = 0
                num -= 1
            else:
                var[num] = augmented_matrix[i][-1]
                for j in range(i + 1, rxc):
                    var[num] = (var[num] - (augmented_matrix[i][j] * var[j])) % 2
                num -= 1

        return var


class LightsOutApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Lights Out Solver")

        self.size = 5
        self.create_grid(self.size)

        
        self.new_game_button = tk.Button(self.root, text="New Game", command=self.clear_grid)
        self.new_game_button.grid(row=0, column=0, columnspan=5, pady=10)

        
        self.solve_button = tk.Button(self.root, text="Solve", command=self.solve_grid)
        self.solve_button.grid(row=self.size + 1, column=0, columnspan=5, pady=10)

    def create_grid(self, size):
        self.solver = LightsOutSolver(size, size)
        self.grid_buttons = [[None for _ in range(size)] for _ in range(size)]

        self.grid_frame = tk.Frame(self.root)
        self.grid_frame.grid(row=1, column=0, columnspan=5, padx=10, pady=10)

        for i in range(size):
            for j in range(size):
                button = tk.Button(self.grid_frame, width=5, height=2, bg="white", command=lambda x=i, y=j: self.toggle_light(x, y))
                button.grid(row=i, column=j, sticky="nsew", padx=2, pady=2)
                self.grid_buttons[i][j] = button

    def toggle_light(self, i, j):
        current_color = self.grid_buttons[i][j].cget("bg")
        if current_color == "white":
            self.grid_buttons[i][j].config(bg="black")
            self.solver.grid[i][j] = 1
        else:
            self.grid_buttons[i][j].config(bg="white")
            self.solver.grid[i][j] = 0

    def solve_grid(self):
        total_matrix = [self.solver.special_vectors(i, j) for i in range(self.solver.rows) for j in range(self.solver.cols)]
        var = self.solver.solve(total_matrix, self.solver.grid)

        
        if var is None:
            messagebox.showerror("No Solution", "No solution exists for the current grid.")
            return

        
        for i in range(self.solver.rows):
            for j in range(self.solver.cols):
                self.grid_buttons[i][j].config(bg="white")

        
        for i in range(self.solver.rows * self.solver.cols):
            if var[i] == 1:
                row = i // self.solver.cols
                col = i % self.solver.cols
                self.grid_buttons[row][col].config(bg="red")

    def clear_grid(self):
        for i in range(self.size):
            for j in range(self.size):
                self.grid_buttons[i][j].config(bg="white")  
                self.solver.grid[i][j] = 0  


if __name__ == "__main__":
    root = tk.Tk()
    app = LightsOutApp(root)
    root.mainloop()
