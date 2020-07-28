;find out how many times sertain element occurs in list
;(A B A C B C A B D) —> ((A 3) (B 3) (C 2) (D 1))  

(defun ifinbl (X Y)
	(cond
		((null Y) nil)
		((eq X (caar Y)) T)
		(T (ifinbl X (cdr Y)))))
(defun add (X Y)
	(cond
		((atom Y) Y)
		((eq X (car Y)) (list X (+ 1 (cadr Y))))
		(T (cons (add X (car Y)) (add X (cdr Y))))))
(defun makel (X Y)
	(if (ifinbl X Y)
		(add X Y)
		(append Y (list (list X 1))) ))
(defun main (X)
	(cond
		((null X) nil)
		(T (makel (car X) (main (cdr X))))))

;all subsets of a given set
;(A B C) —> (NIL (A) (B) (C) (A B) (A C) (B C) (A B C))

(defun connect (A X)
	(cond
		((null X) (list (list A)))
		(T (append (list(cons A (car X))) (connect A (cdr X))))))
(defun comb (X)
	(cond
		((null X) nil)
		(T (append (connect (car X) (comb (cdr X)) ) (comb (cdr X))))))
(defun main (X) (cons nil (comb X)))

;Find first not-NIL atom in list
;((( ) A ) B C) –> A

(defun fnn (X)
	(cond
		((null X) nil)
		((atom X) X)
		((null (fnn (car X))) (fnn (cdr X))) (T (fnn (car X)))))

;Count atoms on sertain level of nesting 
;(A В (B A (C)) A C (A)), 2 —> 3

(defun howmaat (X)
	(cond
		((atom X) 0)
		((atom (car X)) (+ 1 (howmaat (cdr X)))) (T (+ 0 (howmaat (cdr X))))))
(defun howmaatonlvl (X A)
	(cond
		((= A 0) (howmaat X))
		((atom X) 0)
		(T (+ (howmaatonlvl (car X) (- A 1)) (howmaatonlvl (cdr X) A)))))

;how many times each element in list
;(A B A C B C A B D) —> ((A 3) (B 3) (C 2) (D 1))

(defun ifinbl (X Y)
	(cond
		((null Y) nil)
		((eq X (caar Y)) T)
		(T (ifinbl X (cdr Y)))))
(defun add (X Y)
	(cond 
		((atom Y) Y)
		((eq X (car Y)) (list X (+ 1 (cadr Y))))
		(T (cons (add X (car Y)) (add X (cdr Y))))))
(defun makel (X Y) 
	(if (ifinbl X Y)
		(add X Y)
		(append Y (list (list X 1)))))
(defun main (X)
	(cond 
		((null X) nil) 
		(T (makel (car X) (main (cdr X))))))


;remove nesting in list:
;(A (B (C 1) D)) —> (A B C 1 D)

(defun main (LST)
	(cond
		((null LST) nil)
		((atom LST) (list LST))
		(T (append (main (car LST)) (main (cdr LST))))))

;.check if two lists constists of same atoms 

(defun check (X A) ;A - список, Х -элемент. Проверяет есть ли в списке А элемент Х
	(cond
		((null A) nil)
		((eq X (car A)) T)
		(T (check X (cdr A)))))

(defun test (V W)
 		(if (and (null V) (null W)) T
      		(if (check (car V) W)
      			(test (remove (car V) V) (remove (car V) W))
      			nil)))

(defun test (V W)
 		(if (or (null W) (null V))
      		(and (null V) (null W))
      		(if (check (car V) W)
      			(test (remove (car V) V) (remove (car V) W))
      			nil)))

;new list of two lists with this pattern:
;(A B C D) (1 2 4 2) —> ((A) (B B) (C C C C) (D D))

(defun make (X Y)
	(cond
		((= Y 0) nil) 
		((= Y 1) (list X))
		(T (cons X (make X (- Y 1))))))

(defun main (X N) 
	(cond
		((null X) nil)
		(T (cons (make (car X) (car N)) (main (cdr X) (cdr N))))))

;two lists with numbers -> third num list
; Amount of elements is the same with third list. Each element is an amount of elements from first list that are less than element from second list
;(1 7 3 0 2)(3 7 10) —> (3 4 5)

(defun cnt (X Y)
	(cond
		((null X) 0)
		((< (car X) Y) (+ 1 (cnt (cdr X) Y)))
		(T (cnt (cdr X) Y))))

(defun main (X Y)
	(cond 
		((null Y) nil)
		(T (cons (cnt X (car Y)) (main X (cdr Y))))))

;new list of two lists with this pattern:
;but with loop
;(A B C) (1 2 3) —> ((A) (B B) (C C C))

(defun make (symbol n)
	(prog (lst)
		(dotimes (i n)
			(setq lst (cons symbol lst)))
		(return (list lst))))

(defun main (lst amount)
	(prog (ret)
		(dolist (e lst)
			(setq ret (append ret (make e (car amount))))
			(setq amount (cdr amount)))
		(return ret)))

;two lists with numbers -> third num list
;Amount of elements is the same with third list. Each element is an amount of elements from first list that are less than element from second list
;but with loop
;(1 7 3 0 2)(3 7 10) —> (345)

(defun amount (lst border)
	(prog (ret)
		(setq ret 0)
		(dolist (e lst)
			(if (< e border)
				(setq ret (+ ret 1))))
		(return (list ret))))

(defun main (lst lst-of-borders)
	(prog (ret)
		(dolist (border lst-of-borders)
				(setq ret (append ret (amount lst border))))
		(return ret)))

;find last not-nil element in list
;(A B (S 1) ((C)) NIL) —> C

(defun makePlain (lst)
	(cond
		((null lst) nil)
		((atom lst) (list lst))
		(T (append (makePlain (car lst)) (makePlain (cdr lst))))))

(defun main (lst) (car (last (makePlain lst))))

;integers list -> list where each  element is amount of 1, 2, 3... in first list
;(2 1 1 3 1 3 5) —> (3 1 2 0 1)

(defun maxinl (LST)
	(prog (RET)
		(setq RET 0)
		(dolist (E LST)
			(if (> E RET) (setq RET E)))
		(return RET)))

(defun cnt (LST A)
	(prog (RET)
		(setq RET 0)
		(dolist (E LST)
			(if (= E A) (setq RET (+ RET 1))))
		(return RET)))

(defun main (LST)
	(prog (RET M)
		(setq RET nil)
		(setq M (maxinl LST))
		(dotimes (i M)
			(setq RET (append RET (list(cnt LST i)))))
		(return RET)))

;For two-level list return biggest sublist 

(defun lstlen (LST)
	(prog (RET)
		(setq RET 0)
		(dolist (E LST)
			(setq RET (+ RET 1)))
		(return (cons RET LST))))

(defun main (LST)
	(prog (TMP M)
		(setq M `(0))
		(setq TMP nil)
		(dolist (E LST)
			(setq TMP (lstlen E))
			(if (> (car TMP) (car M)) (setq M TMP)))
		(return (cdr M))))




