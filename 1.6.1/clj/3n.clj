(ns programming-challenges.three-n)

(defn- slow-next-value
  [n]
  (if (even? n)
    (/ n 2)
    (+ (* n 3) 1)))

(def next-value (memoize slow-next-value))

(defn- collatz-seq
  ([n]
     (collatz-seq n [n]))
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
