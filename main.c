#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEAT 72

int total_plane = 0;

struct seats {
    int seat_no;
    char *name;
    int age;
    char gender;
    struct seats *next;
};

typedef struct seats seats;

typedef struct {
    int hour;
    int min;
    char meri[3];
} time;

struct plane {
    int plane_no;
    char *from;
    char *to;
    time depart;
    time reach;
    int price;
    seats *list;
    struct plane *next;
};

typedef struct plane plane;

plane *head = NULL, *temp = NULL;

void buff_clear() { while (getchar() != '\n'); }

plane* create_plane() {
    plane *work = (plane*)malloc(sizeof(plane));
    if (head == NULL)
        head = temp = work;
    else {
        temp->next = work;
        temp = temp->next;
    }
    work->next = NULL;
    work->list = NULL;
    total_plane++;
    return work;
}

plane* plane_address(int plane_no) {
    plane *temp = head;
    while (temp != NULL && plane_no != temp->plane_no)
        temp = temp->next;
    return temp;
}

void data_import() {
    FILE *fp = fopen("Flight-details", "r");
    char c[50];
    int i = 0, j = 0, len;

    if (fp == NULL) {
        printf("Import File Missing\n_____Exiting_____");
        exit(1);
    } else {
        while (!feof(fp)) {
            plane *work = create_plane();
            work->plane_no = ++i;

            fscanf(fp, "%s", c);
            len = strlen(c) + 1;
            work->from = (char*)malloc(len);
            strcpy(work->from, c);

            fscanf(fp, "%s", c);
            len = strlen(c) + 1;
            work->to = (char*)malloc(len);
            strcpy(work->to, c);

            fscanf(fp, "%*c%d%*c%d%*c%s", &work->depart.hour, &work->depart.min, work->depart.meri);
            fscanf(fp, "%*c%d%*c%d%*c%s", &work->reach.hour, &work->reach.min, work->reach.meri);
            fscanf(fp, "%*c%d", &work->price);
        }
        fclose(fp);
    }
}

void plane_header() {
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("|   Plane no.  |      From    |    To    |     Depart   |     Reach    |     Price     |\n");
    printf("-------------------------------------------------------------------------------------------------\n");
}

void print_plane(plane *work) {
    printf("|\t%d\t|", work->plane_no);
    printf(" \t%s\t|", work->from);
    printf(" \t%s\t|", work->to);
    printf("   %2d:", work->depart.hour);
    if (work->depart.min)
        printf("%2d", work->depart.min);
    else
        printf("00");
    printf(" %s\t|", work->depart.meri);
    printf("   %2d:", work->reach.hour);
    if (work->reach.min)
        printf("%2d", work->reach.min);
    else
        printf("00");
    printf(" %s\t|", work->reach.meri);
    printf(" \t₹%d\t|\n", work->price);
    printf("-------------------------------------------------------------------------------------------------\n");
}

void info() {
    plane_header();
    for (plane *work = head; work != NULL; work = work->next)
        print_plane(work);
}

void filter(char *from, char *to) {
    plane_header();
    for (plane *work = head; work != NULL; work = work->next) {
        if (!(strcmp(from, work->from) && strcmp(to, work->to)))
            print_plane(work);
    }
}

int seat_taken(plane *work, int seat) {
    seats *hold = work->list;
    while (hold != NULL) {
        if (hold->seat_no == seat)
            return 1;
        hold = hold->next;
    }
    return 0;
}

void seat_print(plane *work, int row) {
    for (int i = row; i < 73; i += 6) {
        if (!seat_taken(work, i)) {
            if (i > 36 && i < 43)
                printf("      %d", i);
            else
                printf("   %d", i);
        } else {
            if (i < 10)
                printf("   X");
            else {
                if (i > 36 && i < 43)
                    printf("      XX");
                else
                    printf("   XX");
            }
        }
    }
}

void print_seat(plane *work) {
    printf("                                       _________\n");
    printf("                                      //       |\n");
    printf("                                     //        |\n");
    printf("                                    //         |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("    ______________________________________________________________________________\n");
    printf("   /      |  ");
    seat_print(work, 1);
    printf(" |      \\\n");
    printf("  /       |  ");
    seat_print(work, 2);
    printf(" |       |\\\\\\\n");
    printf(" /        |  ");
    seat_print(work, 3);
    printf(" |       |///\n");
    printf("| =0 C|    -                                                               |______/\n");
    printf("|          _                                                               |______\n");
    printf("| =0 C|   | ");
    seat_print(work, 4);
    printf(" |      \\\n");
    printf(" \\        | ");
    seat_print(work, 5);
    printf(" |       |\\\\\\\n");
    printf("  \\       | ");
    seat_print(work, 6);
    printf(" |       |///\n");
    printf("   \\______|________________________________________________________________|______/\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    |          |\n");
    printf("                                    \\\\         |\n");
    printf("                                     \\\\        |\n");
    printf("                                      \\\\       |\n");
    printf("                                        --------\n");
}

plane* find_plane() {
    char in, from[15], to[15];
    int i;
    do {
        info();
        printf("\n\nChoose a Plane (or f/F for filter)\n\n->");
        buff_clear();
        scanf("%c", &in);
        if (in == 'f' || in == 'F') {
            printf("\n\nFrom : ");
            scanf("%s", from);
            printf("\nTo : ");
            scanf("%s", to);
            filter(from, to);
            printf("\n\nChoose a Plane (or f/F for filter)\n\n->");
            buff_clear();
            scanf("%c", &in);
        }
        sscanf(&in, "%d", &i);
    } while (!(i > 0 && i < total_plane + 1));
    return (plane_address(i));
}

void add_seat(plane *work, int seat) {
    seats *temp = (seats *)malloc(sizeof(seats));
    char name[50];
    temp->seat_no = seat;
    printf("\nName of the passanger: ");
    buff_clear();
    scanf("%[^\n]s", name);
    temp->name = strdup(name);  // Allocate memory and copy name
    printf("\nAge of the passanger: ");
    scanf("%d", &temp->age);
    printf("\nGender of passanger (M/F): ");
    buff_clear();
    scanf("%c", &temp->gender);
    temp->next = NULL;
    if (work->list == NULL) {
        work->list = temp;
    } else {
        seats *hold = work->list, *old = NULL;
        while (hold != NULL && hold->seat_no < seat) {
            old = hold;
            hold = hold->next;
        }
        temp->next = hold;
        if (old != NULL) old->next = temp;
        else work->list = temp;
    }
}
void data_export() {
    FILE *fp = fopen("Flight-details", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    plane *work = head;
    while (work != NULL) {
        fprintf(fp, "%s %s %02d:%02d%s %02d:%02d%s %d\n", 
            work->from, work->to, 
            work->depart.hour, work->depart.min, work->depart.meri,
            work->reach.hour, work->reach.min, work->reach.meri,
            work->price);

        seats *seat = work->list;
        while (seat != NULL) {
            fprintf(fp, "%d %s %d %c\n", seat->seat_no, seat->name, seat->age, seat->gender);
            seat = seat->next;
        }
        work = work->next;
    }

    fclose(fp);
    printf("Flight details successfully saved.\n");
}

void book_seat(plane *work) {
    int seat;
    do {
        print_seat(work);
        printf("\n\nSeat no.: ");
        scanf("%d", &seat);
    } while (!(seat > 0 && seat < MAX_SEAT + 1) || seat_taken(work, seat));
    add_seat(work, seat);
    data_export();  
}

void remove_seat(plane *work) {
    int seat;
    seats *hold = work->list, *old = NULL;
    do {
        printf("Seat no.: ");
        scanf("%d", &seat);
    } while (!(seat > 0 && seat < MAX_SEAT + 1));
    while (hold != NULL && hold->seat_no < seat) {
        old = hold;
        hold = hold->next;
    }
    if (hold == NULL || hold->seat_no != seat) {
        printf("\n\tSeat not found");
        return;
    }
    if (old != NULL) old->next = hold->next;
    else work->list = hold->next;
    free(hold->name);
    free(hold);
    data_export(); 
}


void booked_info(plane *work) {
    seats *hold = work->list;
    printf("-----------------------------------------------------------------------------");
    printf("\n| Seat no. |    Name    |    Age    |    Gender     |\n");
    printf("-----------------------------------------------------------------------------");
    while (hold != NULL) {
        printf("\n|    %d\t   |", hold->seat_no);
        printf(" \t%s\t|", hold->name);
        printf("    %d\t  |", hold->age);
        printf("    %c\t  |", hold->gender);
        hold = hold->next;
    }
    printf("\n-----------------------------------------------------------------------------");
}



int main() {
    int choice;
    data_import();
    plane *work = NULL;
    while (1) {
        printf("\n\nSelect Choice\n1. Book Seat\n2. Remove Seat\n3. Show All Plane\n4. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                work = find_plane();
                book_seat(work);
                break;
            case 2:
                work = find_plane();
                remove_seat(work);
                break;
            case 3:
                info();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    }
}
