(ns swagger-petstore.core-test
  (:require [clojure.java.io :as io]
            [clojure.test :refer :all]
            [swagger-petstore.core :refer :all])
  (:import (java.text ParseException)))

(deftest test-api-context
  (testing "default"
    (is (= {:base-url        "http://petstore.swagger.io/v2"
            :date-format     "yyyy-MM-dd"
            :datetime-format "yyyy-MM-dd'T'HH:mm:ss.SSSXXX"
            :debug           false}
           default-api-context
           *api-context*
           (with-api-context {}
             *api-context*))))
  (testing "customize via with-api-context"
    (with-api-context {:base-url "http://localhost" :debug true}
      (is (= {:base-url        "http://localhost"
              :date-format     "yyyy-MM-dd"
              :datetime-format "yyyy-MM-dd'T'HH:mm:ss.SSSXXX"
              :debug           true}
             *api-context*))
      ;; nested with-api-context inherits values from the outer api context
      (with-api-context {:datetime-format "yyyy-MM-dd HH:mm:ss"}
        (is (= {:base-url        "http://localhost"
                :date-format     "yyyy-MM-dd"
                :datetime-format "yyyy-MM-dd HH:mm:ss"
                :debug           true}
               *api-context*))))
    ;; back to default api context
    (is (= {:base-url        "http://petstore.swagger.io/v2"
            :date-format     "yyyy-MM-dd"
            :datetime-format "yyyy-MM-dd'T'HH:mm:ss.SSSXXX"
            :debug           false}
           *api-context*))))

(deftest test-check-required-params
  (let [a nil b :not-nil]
    (is (thrown? IllegalArgumentException (check-required-params a)))
    (is (nil? (check-required-params b)))))

(deftest test-parse-and-format-date
  (testing "default date format"
    (is (= "2015-11-07" (-> "2015-11-07T03:49:09.356+00:00" parse-datetime format-date)))
    (is (= "2015-11-07" (-> "2015-11-07" parse-date format-date)))
    (is (thrown? ParseException (parse-date "2015-11"))))
  (testing "custom date format: without day"
    (with-api-context {:date-format "yyyy-MM"}
      (is (= "2015-11" (-> "2015-11-07T03:49:09.123Z" parse-datetime format-date)))
      (is (= "2015-11" (-> "2015-11" parse-date format-date)))
      (is (thrown? ParseException (parse-date "2015"))))))

(deftest test-parse-and-format-datetime
  (testing "default datetime format"
    (are [s]
      (is (= "2015-11-07T03:49:09.356Z" (-> s parse-datetime (format-datetime "UTC"))))
      "2015-11-07T03:49:09.356+00:00"
      "2015-11-07T05:49:09.356+02:00"
      "2015-11-07T02:49:09.356-01:00"
      "2015-11-07T03:49:09.356Z")
    (is (thrown? ParseException (parse-datetime "2015-11-07 03:49:09"))))
  (testing "custom datetime format: without milliseconds"
    (with-api-context {:datetime-format "yyyy-MM-dd'T'HH:mm:ssXXX"}
      (are [s]
        (is (= "2015-11-07T13:49:09+10:00" (-> s parse-datetime (format-datetime "GMT+10"))))
        "2015-11-07T03:49:09+00:00"
        "2015-11-07T03:49:09Z"
        "2015-11-07T00:49:09-03:00")
      (is (thrown? ParseException (parse-datetime "2015-11-07T03:49:09.123Z"))))))

(deftest test-param-to-str
  (let [date (parse-datetime "2015-11-07T03:49:09.123Z")]
    (are [param expected]
      (is (= expected (param-to-str param)))
      nil ""
      "abc" "abc"
      123 "123"
      1.0 "1.0"
      [12 "34"] "12,34"
      date (format-datetime date))))

(deftest test-make-url
  (are [path path-params url]
    (is (= url (make-url path path-params)))
    "/pet/{petId}" {"petId" 123} "http://petstore.swagger.io/v2/pet/123"
    "/" nil "http://petstore.swagger.io/v2/"
    "/pet" {"id" 1} "http://petstore.swagger.io/v2/pet"
    "/pet/{id}" nil "http://petstore.swagger.io/v2/pet/{id}"))

(deftest test-normalize-param
  (let [file (-> "hello.txt" io/resource io/file)]
    (are [param expected]
      (is (= expected (normalize-param param)))
      [12 "34"] ["12" "34"]
      file file
      "abc" "abc"
      [[12 "34"] file "abc"] [["12" "34"] file "abc"])))

(deftest test-normalize-params
  (is (= {:a "123" :b ["4" ["5" "6"]]}
         (normalize-params {:a 123 :b [4 [5 "6"]] :c nil}))))

(deftest test-json-mime?
  (are [mime expected]
    (is (= expected (boolean (json-mime? mime))))
    :json true
    "application/json" true
    "application/json; charset=utf8" true
    nil false
    :xml false
    "application/pdf" false))

(deftest test-json-preferred-mime
  (are [mimes expected]
    (is (= expected (json-preferred-mime mimes)))
    ["application/xml" "application/json"] "application/json"
    [:json] :json
    [] nil
    nil nil
    ["application/xml"] "application/xml"))

(deftest test-serialize
  (is (= "{\"aa\":1,\"bb\":\"2\"}" (serialize {:aa 1 :bb "2"} :json)))
  (is (= "{}" (serialize {} "application/json")))
  (is (= "[1,\"2\"]" (serialize [1 "2"] "application/json; charset=UTF8")))
  (is (thrown? IllegalArgumentException (serialize {} "application/xml"))))

(deftest test-deserialize
  (are [body content-type expected]
    (is (= expected (deserialize {:body body :headers {:content-type content-type}})))
    "{\"aa\": 1, \"bb\": \"2\"}" "application/json" {:aa 1 :bb "2"}
    "[1, \"2\"]" "application/json; charset=UTF8" [1 "2"]
    "{invalid json}" "application/json" "{invalid json}"
    "plain text" "text/plain" "plain text"))