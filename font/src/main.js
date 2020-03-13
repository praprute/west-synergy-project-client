import Vue from 'vue'
import App from './App.vue'
import VueRouter from 'vue-router'
import BootstrapVue from 'bootstrap-vue'
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'
import Header from './components/Header'
import * as VueGoogleMaps from "vue2-google-maps";
import Chart from 'chart.js'
import Chartkick from 'vue-chartkick'
import { Datetime } from 'vue-datetime'
import 'vue-datetime/dist/vue-datetime.css'

import {
  routes
} from './rout'
import {
  store
} from './storage'

Vue.config.productionTip = false

Vue.use(Datetime)
Vue.use(Chartkick.use(Chart))
Vue.use(VueRouter)
Vue.use(BootstrapVue)
Vue.use(VueGoogleMaps, {
  load: {
    key: "AIzaSyBXrL8n6ambWLdpEd5hV3q0i2JozoGqR-M",
    libraries: "places"
  }
});

Vue.component('datetime', Datetime);
Vue.component('header-navbar', Header)

const router = new VueRouter({
  routes
});

new Vue({
  render: h => h(App),
  store,
  router
}).$mount('#app')
