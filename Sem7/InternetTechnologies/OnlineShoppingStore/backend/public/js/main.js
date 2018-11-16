var app = new Vue({
  el: '#app',
  data() {
    return {
      api: "http://localhost:15000/api/products/",
      page: 1,
      sort: 'discounted',
      products: []
    }
  },
  computed: {
    
  },
  created() {
    this.getProducts()
  },
  methods: {
    async getProducts() {
      params = {
        p: this.page,
        sort: this.sort
      }

      console.log(`Fetching products`);
      console.log(params);
      const response = await axios.get(this.api, {
        params
      })
      console.log(await response.data);
      this.products = await response.data.data
      this.pages = await response.data.pages
    },
    changeSort(sort) {
      if (this.sort === sort) {
        this.ord = this.ord === 'asc' ? 'dsc' : 'asc'
      } else {
        this.sort = sort
      }
      this.getFlights()
    }
  },
  mounted() {}
})