#import <UIKit/UIKit.h>
#import <objc/runtime.h>

static inline void cd_swizzling(Class cla, SEL original, SEL swizzled) {
    Method originalMethod = class_getInstanceMethod(cla, original);
    Method swizzledMethod = class_getInstanceMethod(cla, swizzled);
    BOOL didAddMethod = class_addMethod(cla, original, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
    if (didAddMethod) {
        class_replaceMethod(cla, swizzled, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
    } else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

