;Lisp Übungsblatt2 PR3

;Diana Beldiman 1513454
;Santino Nobile 1414417
;Marco Präg 1613370



(setq baum '(8(4(2(1 nil nil)(3 nil nil))(6 nil nil))(12 (10 nil (11 nil nil)) nil)))

 ;(V L R)
 
(defun vater (tree)
 (car tree))
 
(defun right (tree)
 (caddr tree))
 
(defun left (tree)
 (cadr tree))
 
(defun make-tree (vater left right)
 (cond
  ((null vater)nil)
   (T(list vater left right))))
 
 ;IsEmpty

(defun isEmpty (tree)
 (cond
  ((null (car tree)) t)))
  


 ;GetMin

;defun getMin (tree)
 ;(cond 
 ;((isEmpty tree) nil)
  ;((isEmpty (left tree))(vater tree))
  ;(T(getMin (left tree)))))
  
(defun getMin (tree)
 (cond 
  ((not(isEmpty (left tree)))(getMin(left tree)))
  (T(car tree))))
  

 ;GetMax

;(defun getMax (tree)
 ;(cond 
  ;((isEmpty tree) nil)
  ;((isEmpty (right tree))(vater tree))
  ;(T(getMax (right tree)))))
  
(defun getMax (tree)
 (cond 
  ((not(isEmpty (right tree)))(getMax(right tree)))
  (T(car tree))))
  

 ;Size
 
(defun size (tree)
  (cond
   ((null tree) 0)
   ((listp (car tree)) (size (append (car tree) (cdr tree)))) 
   (T(+ 1 (size (cdr tree))))))
   
   
 ;Height
 
(defun calculateHeight (tree counter)
  (cond
   ((null tree) counter)
   (T(max (calculateHeight (left tree) (+ 1 counter)) (calculateHeight (right tree) (+ 1 counter))))))
   
  (defun height (tree)
   (calculateHeight tree -1))
   
   
 ;Contains
  
 (defun containsval (x baum)
 (cond ((null baum) nil)
  ((= x (vater baum)) (true))
  ((< x (vater baum)) 
  (containsval x (left baum)) )
  ((> x (vater baum)) 
  (containsval x (right baum)))))
  
  
 ;Insert

 (defun insertval (x baum)
  (cond 
  ((null baum) (make-tree x nil nil))
  ((= x (vater baum)) baum)
  ((< x (vater baum)) 
  (make-tree (vater baum) (insertval x (left baum)) (right baum)))
  ((> x (vater baum)) (make-tree (vater baum)
  (left baum) (insertval x (right baum))))))
   
   
 ;Remove
   
  (defun removeVal (key baum)
   (cond ((null baum) nil)
    ((= key (vater baum))  (make-tree (getmin (right baum)) (left baum) (removeVal  (getmin (right baum))(right baum))))
    ((< key (vater baum)) 
    (make-tree (vater baum) (removeVal key (left baum)) (right baum)))
    ((> key (vater baum)) (make-tree (vater baum)
    (left baum) (removeVal key (right baum))))))


 ;AddAll

(defun addAll (othertree tree )
 (cond
  ((null tree) othertree)
  ((null othertree) tree)
  (T (setq tree (insertVal (vater othertree) tree))
     (setq tree (addAll (left othertree) tree ))
	 (setq tree (addAll (right othertree) tree )))))


 ;printLevelOrder

;(defun loopingLoo (tree)
 ;(setq i 1)
 ;(loop while (< i (height tree)) do
  ;(printLevelOrder tree i)
  ;(setq i (+ i 1))))
    
(defun printLevelOrder (tree)
 (setq i 1)
 (loop while (<= i (+ 1 (height tree))) do
  (helpPrintLevelOrder tree i)
 (setq i (+ i 1))
       (terpri)))
	   
(defun helpPrintLevelOrder (tree level)
 (cond
  ((null tree)nil)
  ((= level 1) (princ (vater tree)) (princ " "))
  ((> level 1) (helpPrintLevelOrder (left tree) (- level 1))
               (helpPrintLevelOrder (right tree) (- level 1)))))

			   
 ;Insertfile
 
(defun insertfile (tree filename)
    (setq elements (readFile filename))
	(loop while (not(null elements)) do
	 (cond
	  ((numberp (car elements))
      (setq tree (insertval (car elements) tree))))
	 (setq elements (cdr elements)))tree)
	
	
(defun readFile (filename)
    (with-open-file (stream filename :direction :input :if-does-not-exist nil )
        (loop for line = (read stream nil 'eof)
            until(eq line 'eof)
            collect line))) ;Sammelt alle Elemente in eine Liste
			
			
 ;Menu

(defun p(x) (princ x) (terpri)) ;terpri -> newline
(defun p1(x) (princ x) (princ " "))

(defun menu ()
(setq in -1)
(setq tree nil)
(loop while (not (= in 0)) do
 (p "Menü")
 (p "1 : Baum erstellen")
 (p "2 : Element einfügen")
 (p "3 : Kleinstes Element")
 (p "4 : Größtes Element")
 (p "5 : Prüfen ob Baum leer")
 (p "6 : Element entfernen")
 (p "7 : Levelorder")
 (p "8 : Höhe des Baumes")
 (p "9 : Elemente eines Baumes hinzufügen")
 (p "10: Prüfen ob ein bestimmtes Element vorhanden ist")
 (p "11: Elemente aus einer Datei hinzufügen")
 (p "12: Anzahl nicht-leerer Knoten")
 (p "0 : Menü beenden")
 (p "Option eingeben ==> ")
 (setq op (read))
   (case op
     (1 (p "Bitte fügen Sie ein erstes Element in den leeren Baum ein (Nil ist erlaubt)") (p (setq tree (make-tree (read) nil nil))))
     (2 (p "Element einfügen") (p (setq tree (insertval (read) tree))))
     (3 (p "Kleinstes Element") (p (getmin tree)))
	 (4 (p "Größtes Element") (p (getmax tree)))
	 (5 (p "Prüfen ob baum leer") (p (isempty tree)))
	 (6 (p "Element entfernen") (p(setq tree (removeVal (read) tree))))
	 (7 (p "Levelorder") (printLevelOrder tree))
	 (8 (p "Höhe des Baumes") (p(height tree)))
	 (9 (p "Elemente eines anderen Baumes zum jetzigen Baum hinzufügen") (p (setq tree (addAll (read) tree))))
     (10 (p "Prüfen ob ein bestimmtes Element vorhanden ist") (p (containsval (read) tree)))
	 (11 (p "Elemente aus einer Datei hinzufügen") (p (setq tree (insertfile tree (read)))))
	 (12 (p "Anzahl nicht-leerer Knoten") (p (size tree)))
     (0 (p "Bye") (setq in 0)))))
