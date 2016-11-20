//
//  main2.c
//  DICTIONNAIRE - PART 2
//
//  Created by Bérangère La Touche on 20/11/2016.
//  Copyright © 2016 PROJECT SEMAINE C. All rights reserved.
//

#include <stdio.h>
#include "gestrech.h"

int main(int argc, const char * argv[]) {
    
    LinkedList* dictionarys = newElement(NULL);
    
    menu(dictionarys);
    
    return 0;
}
