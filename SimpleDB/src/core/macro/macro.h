//
//  macro.h
//  SimpleDB
//
//  Created by OYOL on 2019/6/21.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef macro_h
#define macro_h

#define SDBlikely(_condition_)   __builtin_expect(!!(_condition_), 1)
#define SDBunlikely(_condition_) __builtin_expect(!!(_condition_), 0)


#endif /* macro_h */
