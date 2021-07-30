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
    
    func displayTable(_ orders: [[String]]) -> [[String]] {
        
        var tableDict:[String:[String:Int]] = [:]
        var menuSet = Set<String>()
        for order in orders {
            if tableDict[order[1]] == nil {
                tableDict[order[1]] = [:]
            }
            if tableDict[order[1]]?[order[2]] == nil {
                tableDict[order[1]]?[order[2]] = 1
            }else{
                tableDict[order[1]]![order[2]]! += 1
            }
            menuSet.insert(order[2])
        }
        var menuArray:[String] = []
        for menu in menuSet {
            menuArray.append(menu)
        }
        // 菜单名从小到大排序
        menuArray.sort { (string1, string2) -> Bool in
            return string1.compare(string2) == .orderedAscending
        }
        
        var result:[[String]] = []
        var tableArray:[String] = []
        for (key, _) in tableDict {
            tableArray.append(key)
        }
        // 餐桌号从小到大排序
        tableArray.sort { (string1, string2) -> Bool in
            return Int(string1) ?? 0 < Int(string2) ?? 0
        }
        for tableNum in tableArray {
            var tmpArray:[String] = [tableNum]
            for menuName in menuArray {
                let count = tableDict[tableNum]?[menuName] ?? 0
                tmpArray.append("\(count)")
            }
            result.append(tmpArray)
        }
        menuArray.insert("Table", at: 0)
        result.insert(menuArray, at: 0)
        
        return result
    }
}


class Solution {

    func findInsertIndex(value:Int, dArray:[Int]) -> Int {
        var left = 0
        var right = dArray.count-1
        while left < right {
            let mid = (left+right)/2
            if dArray[mid] < value {
                left = mid+1
            }else{
                right = mid-1
            }
        }
        if dArray[left] >= value  {
            return left
        }else{
            return left+1
        }
    }

    func minOperations(_ target: [Int], _ arr: [Int]) -> Int {
        var targetIndex:[Int:Int] = [:]
        var index = 0
        for intValue in target {
            targetIndex[intValue] = index
            index += 1
        }
        var arrIndex:[Int] = []
        for intValue in arr {
            if let index = targetIndex[intValue] {
                arrIndex.append(index)
            }
        }
        
        var dArray:[Int] = []
        if arrIndex.count > 0 {
            dArray.append(arrIndex[0])
        }
        var i = 1
        while i < arrIndex.count {
            let value = arrIndex[i]
            if value > dArray.last! {
                // 直接拼在后面
                dArray.append(value)
            }else{
                // 找出不小于value的且最接近value的数(替换)
                dArray[findInsertIndex(value: value, dArray: dArray)] = value
            }
            i += 1
        }
        
        return target.count-dArray.count
    }
}


class Solution {
    func restoreArray(_ adjacentPairs: [[Int]]) -> [Int] {
        var dict:[Int:[Int]] = [:]
        for pair in adjacentPairs {
            if dict[pair[0]] != nil {
                dict[pair[0]]?.append(pair[1])
            }else{
                dict[pair[0]] = [pair[1]]
            }
            if dict[pair[1]] != nil {
                dict[pair[1]]?.append(pair[0])
            }else{
                dict[pair[1]] = [pair[0]]
            }
        }
        
        var firstValue:Int = 0
        for (key, array) in dict {
            if array.count == 1 {
                firstValue = key
                break
            }
        }
        
        var result:[Int] = [firstValue]
        var preValue:Int? = firstValue
        var nextValue:Int? = dict[firstValue]?[0]
        
        while nextValue != nil {
            result.append(nextValue!)
            if let array = dict[nextValue!] {
                if array[0] != preValue {
                    preValue = nextValue
                    nextValue = array[0]
                }else if array.count > 1{
                    preValue = nextValue
                    nextValue = array[1]
                }else{
                    break
                }
            }
        }
        return result
    }
}
