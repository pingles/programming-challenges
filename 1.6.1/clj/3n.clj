(ns programming-challenges.three-n)

(defn- next-value
  [n]
  (if (even? n)
    (/ n 2)
    (+ (* n 3) 1)))

(defn- collatz-seq
  ([n]
     (collatz-seq n (list n)))
  ([n xs]
     (lazy-seq
      (if (= n 1)
        xs
        (let [val (next-value n)]
          (collatz-seq val (conj xs val)))))))

(defn max-cycle-length
  [i j]
  (apply max
         (map #(count (collatz-seq %))
              (range i j))))

;; (time (max-cycle-length 100 200))
;; "Elapsed time: 1.684 msecs"
;; 125
