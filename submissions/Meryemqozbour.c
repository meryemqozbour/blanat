#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITY_LEN 50
#define MAX_PRODUCT_LEN 50
#define MAX_LINE_LEN 100
#define MAX_ENTRIES 1000000

typedef struct {
    char city[MAX_CITY_LEN];
    char product[MAX_PRODUCT_LEN];
    double price;
} Entry;

int compare_entries(const void *a, const void *b) {
    Entry *entry_a = (Entry *)a;
    Entry *entry_b = (Entry *)b;
    
    if (entry_a->price != entry_b->price) {
        return (entry_a->price < entry_b->price) ? -1 : 1;
    } else {
        return strcmp(entry_a->product, entry_b->product);
    }
}

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }
    
    Entry entries[MAX_ENTRIES];
    int num_entries = 0;
    
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), input_file) && num_entries < MAX_ENTRIES) {
        sscanf(line, "%[^,],%[^,],%lf", entries[num_entries].city, entries[num_entries].product, &entries[num_entries].price);
        num_entries++;
    }
    
    fclose(input_file);
    
    qsort(entries, num_entries, sizeof(Entry), compare_entries);
    
    double min_price = entries[0].price;
    char cheapest_city[MAX_CITY_LEN];
    strcpy(cheapest_city, entries[0].city);
    
    double total_price = 0.0;
    int printed_products = 0;
    
    fprintf(output_file, "%s ", cheapest_city);
    
    for (int i = 0; i < num_entries && printed_products < 5; i++) {
        if (strcmp(entries[i].city, cheapest_city) == 0) {
            total_price += entries[i].price;
            if (i == 0 || strcmp(entries[i].product, entries[i - 1].product) != 0) {
                fprintf(output_file, "\n%s %.2lf", entries[i].product, entries[i].price);
                printed_products++;
            }
        } else {
            break;
        }
    }
    
    fprintf(output_file, "\n");
    fclose(output_file);
    
    return 0;
}
