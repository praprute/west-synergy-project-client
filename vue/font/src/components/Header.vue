<template>

  <b-navbar toggleable="lg" type="dark" variant="info">
    <b-container>
    <b-navbar-brand href="./first.vue">WASTE ENERGY</b-navbar-brand>

    <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

    <b-collapse id="nav-collapse" is-nav >
      <b-navbar-nav class="ml-auto">
        <b-nav-item href="#">Realtime</b-nav-item>
        <b-nav-item href="#">History</b-nav-item>
      </b-navbar-nav>
    </b-collapse>
    </b-container>
  </b-navbar>
  
</template>

<script>
export default {
    data(){
      return{

      };
    },
    methods:{
      // lookhistory(){
      //   this.$router.push("/history")
      // }
    }
}
</script>

<style lang="css" >

a.nav-link{
  color: #ffffff !important;
}

</style>