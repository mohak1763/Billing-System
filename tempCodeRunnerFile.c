        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;;
            printf("\nPlease enter the quantity : \t");
            scanf("%d",&ord.itm[i].qty);
            printf("\nPlease enter the unit price : \t");
            scanf("%f",&ord.itm[i].price);


        }