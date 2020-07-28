#в каждом узле дерева  содержится информация о студенте фамилия нмер зачетки и 5 оценок экз.
#напечатать фамилии студентов со среднем баллом ниже 3.5 ключ - номер зач книжки
#3.5 = 37.5

from enum import Enum

class dataClass:
	def __init__(self):
		self.number = None
		self.surname = None
		self.algorithms = None
		self.math = None
		self.english = None
		self.oop = None
		self.peripherals = None
	def fromLine(self, line):
		self.number = int(line[0])
		self.surname = line[1]
		self.algorithms = int(line[2])
		self.math = int(line[3])
		self.english = int(line[4])
		self.oop = int(line[5])
		self.peripherals = int(line[6])
	def badStudent(self):
		if (self.algorithms + self.math + self.english + self.oop + self.peripherals) / 5 < 37.5:
			return True
		return False
	def retString(self):
		return 'number:' + str(self.number) + ' surname:' + self.surname + ' alg:' + str(self.algorithms) + ' math:' + str(self.math) + ' eng:' + str(self.english) + ' oop:' + str(self.oop) + ' periph:' + str(self.peripherals)

class Color(Enum):
    BLACK = 0
    RED = 1

class Node():
    def __init__(self, data, color = Color.BLACK):
        self.data = data
        self.color = color
        self.left = None
        self.right = None
        self.parent = None

class RedBlackTree():
    def __init__(self):
        self.nil = Node(None)
        self.nil.left = self.nil
        self.nil.right = self.nil
        
        self.root = self.nil

    #Добавление узла
    def add(self, node):
        # Если корень
        if self.root == self.nil:
            self.root = node
            self.root.color = Color.BLACK

            node.left = self.nil
            node.right = self.nil
            node.parent = self.nil
            return

        # Поиск родителя для вставки
        current_node = self.root
        while current_node != self.nil:
            parent = current_node
            if node.data.number < current_node.data.number:
                current_node = current_node.left
            else:
                current_node = current_node.right

        #Вставка узла
        node.parent = parent
        if node.data.number < parent.data.number:
            parent.left = node
        else:
            parent.right = node
        node.left = self.nil
        node.right = self.nil

        #Балансировка
        self.add_fix(node)

    #Балансировка после добавления узла
    def add_fix(self, node):
        #Пока отец красный
        while node.parent.color == Color.RED:
            #Отец левый ребенок
            if node.parent == node.parent.parent.left:
                uncle = node.parent.parent.right
                #Если дядя красный,
                #перекрашиваем отца и дядю в черный,
                #а деда в красный
                if uncle.color == Color.RED:
                    node.parent.color = Color.BLACK
                    uncle.color = Color.BLACK
                    node.parent.parent.color = Color.RED

                    node = node.parent.parent
                #Дядя черный
                else:
                    #Если узел правый потомок, 
                    #то сначала левый поворот
                    if node == node.parent.right:
                        node = node.parent
                        self.left_rotate(node)
                    #Отца в черный, деда в красный 
                    #и правый поворот вокруг деда 
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self.right_rotate(node.parent.parent)
            #Отец правый ребенок
            else:
                uncle = node.parent.parent.left
                #Если дядя красный,
                #перекрашиваем отца и дядю в черный,
                #а деда в красный
                if uncle.color == Color.RED:
                    node.parent.color = Color.BLACK
                    uncle.color = Color.BLACK
                    node.parent.parent.color = Color.RED

                    node = node.parent.parent
                #Дядя черный
                else:
                    #Если узел левый потомок, 
                    #то сначала правый поворот
                    if node == node.parent.left:
                        node = node.parent
                        self.right_rotate(node)
                    #Отца в черный, деда в красный 
                    #и левый поворот вокруг деда
                    node.parent.color = Color.BLACK
                    node.parent.parent.color = Color.RED
                    self.left_rotate(node.parent.parent)

        #Корень всегда черный
        self.root.color = Color.BLACK

    #Левый поворот
    def left_rotate(self, node):
        root = node.right
        node.right = root.left

        if root.left != self.nil:
            root.left.parent = node

        root.parent = node.parent

        if node.parent == self.nil:
            self.root = root
        elif node == node.parent.left:
            node.parent.left = root
        else:
            node.parent.right = root

        root.left = node
        node.parent = root

    #Правый поворот
    def right_rotate(self, node):
        root = node.left
        node.left = root.right

        if root.right != self.nil:
            root.right.parent = node

        root.parent = node.parent

        if node.parent == self.nil:
            self.root = root
        elif node == node.parent.right:
            node.parent.right = root
        else:
            node.parent.left = root

        root.right = node
        node.parent = root

    #Вывод в файл
    def printToFile(self, node, file):
        if self.root == self.nil:
            print("empty", file = file)
            return
        if node != self.nil:
            # Вывод узла
            if node.color == Color.BLACK:
                backgr = "BLACK "
            else:
                backgr = "RED "
            print(backgr + "node: " + node.data.retString() + "\n", file = file)

            # Вывод его левого сына
            if node.left != self.nil:
                if node.left.color == Color.BLACK:
                    backgr = "BLACK "
                else:
                    backgr = "RED "
                print("\t" + backgr + "left: "  + node.left.data.retString(), file = file)
            else:
            	print("\t" + "left: " + " NIL" ,file = file)

            # Вывод его правого сына
            if node.right != self.nil:
                if node.right.color == Color.BLACK:
                    backgr = "BLACK "
                else:
                    backgr = "RED "
                print("\t"  + backgr + "right: " + node.right.data.retString() + "\n\n", file = file)
            else:
            	print("\t" + "right: " +" NIL" + "\n\n", file = file)

            self.printToFile(node.left, file)
            self.printToFile(node.right, file)

    def showBad(self, node, file):
        if self.root == self.nil:
            print("\tEmpty")
            return
        if node != self.nil:
            # Вывод узла
            if node.data.badStudent():
            	print(node.data.surname, end = '\n', file = file)

            self.showBad(node.left, file)
            self.showBad(node.right, file)

def main():
    tree = RedBlackTree()

    with open("input.dat", "r") as file:
        for line in file:
            data = dataClass()
            data.fromLine(line.split())
            tree.add(Node(data, color = Color.RED))

    with open("output.dat", "w") as file:
    	print("Red black tree:", end = '\n', file = file)
    	tree.printToFile(tree.root, file)
    	print("Bad students:", end = '\n', file = file)
    	tree.showBad(tree.root, file)

if __name__ == "__main__":
    main()
