(ns programming-challenges.three-n)

(defn- next-value
  [n]
  (if (even? n)
    (/ n 2)
    (+ (* n 3) 1)))

(defn- collatz-seq
  ([n]
     (collatz-seq n [n]))
  ([n xs]
     (if (= n 1)
       xs
       (let [val (next-value n)]
         (collatz-seq val (conj xs val))))))
