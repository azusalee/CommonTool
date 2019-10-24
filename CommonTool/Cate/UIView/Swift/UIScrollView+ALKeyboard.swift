//
//  UIScrollView+BTSKeyboard.swift
//  tasker
//
//  Created by yangming on 2018/11/1.
//  Copyright © 2018年 BT. All rights reserved.
//

import UIKit

extension UIScrollView {
    /// 监听键盘，自动调节offset，在viewwillappear調用
    func al_addKeyboardNotification() {
        NotificationCenter.default.addObserver(self, selector: #selector(UIScrollView.al_keyboardWillAppear(notification:)), name: UIResponder.keyboardWillShowNotification, object: nil)
    }
    
    /// 移除键盘监听，在viewwilldisappear調用
    func al_removeKeyboardNotification() {
        NotificationCenter.default.removeObserver(self, name: UIResponder.keyboardWillShowNotification, object: nil)
    }
    
    /// 键盘出现
    @objc
    func al_keyboardWillAppear(notification: Notification) {
        if let responseView = self.al_getResponseView(pView: self) {
            let user_info = notification.userInfo
            let keyboardRect = (user_info?[UIResponder.keyboardFrameEndUserInfoKey] as! NSValue).cgRectValue
            if let responseRect = responseView.superview?.convert(responseView.frame, to: UIApplication.shared.keyWindow) {
                let responseBottomInScrollView = responseRect.origin.y+responseRect.size.height+10
                let moveOffset = responseBottomInScrollView-keyboardRect.origin.y;
                
                if moveOffset > 0 {
                    var originOffset = self.contentOffset;
                    originOffset.y += moveOffset;
                    self.setContentOffset(originOffset, animated: true)
                }
            }
            
        }
    }
    
    /// 獲取正在響應的view
    func al_getResponseView(pView:UIView) -> UIView? {
        if pView.isFirstResponder == true {
            return pView
        }
        for subView in pView.subviews {
            let responseView = self.al_getResponseView(pView: subView)
            if responseView != nil {
                return responseView
            }
        }
        return nil
    }
}
