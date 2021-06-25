//
//  leetCodeSwift.swift
//  CommonTool
//
//  Created by lizihong on 2021/5/8.
//  Copyright © 2021 AL. All rights reserved.
//

import Foundation

public class Employee {
    public var id: Int
    public var importance: Int
    public var subordinates: [Int]
    public init(_ id: Int, _ importance: Int, _ subordinates: [Int]) {
        self.id = id
        self.importance = importance
        self.subordinates = subordinates
    }
}


class Solution {
    func getImportance(employeesDict: [Int:Employee], id: Int) -> Int {
        if let employee = employeesDict[id] {
            var result = employee.importance
            for subID in employee.subordinates {
                result += getImportance(employeesDict: employeesDict, id: subID)
            }
            return result
        }
        return 0
    }

    func getImportance(_ employees: [Employee], _ id: Int) -> Int {
        
        var employeesDict: [Int:Employee] = [:]
        for employee in employees {
            employeesDict[employee.id] = employee
        } 
        return getImportance(employeesDict: employeesDict, id: id)
    }
}

// 692. 前K个高频单词
extension Solution {
    func topKFrequent(_ words: [String], _ k: Int) -> [String] {
        var map = [String: Int]()
        words.forEach { map[$0, default: 0] += 1}
        let sorted = map.sorted {
            return $0.value > $1.value || ($0.value == $1.value && $0.key < $1.key)
        }
        return sorted[0..<k].map { $0.key }
    }
}
