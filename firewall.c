#include "firewall.h"

/* 1-я для входящих пакетов */
/* 2-я для исходящих пакетов */
struct nf_hook_ops nf_incoming;
struct nf_hook_ops nf_outgoing;

/* функция обработки */
static unsigned int Hook_Func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    pr_info("[*] Packet dropped !");
	return NF_DROP; /* отбрасываем все пакеты */
}

static int  __init mod_init(void)
{
    /* Заполнение структур */
    /* Сначала, заполним структуру для входящих пакетов */
    nf_incoming.hook = Hook_Func; /* указатель на нашу функцию */
    nf_incoming.pf = PF_INET; /* Семейство протоколов */
    nf_incoming.hooknum = NF_INET_PRE_ROUTING; /* Указываем, в каком месте будет срабатывать функция */
    nf_incoming.priority = NF_IP_PRI_FIRST;/* Выставляем самый высокий приоритет для функции */

    /* Тоже самое для исходящих */
    nf_outgoing.hook = Hook_Func;
    nf_outgoing.pf = PF_INET;
    nf_outgoing.hooknum = NF_INET_PRE_ROUTING;
    nf_outgoing.priority = NF_IP_PRI_FIRST;

    nf_register_hook(&nf_incoming);
    nf_register_hook(&nf_outgoing);
    pr_info("[*] FireWall loaded !\n");
    return 0;
}

static void __exit mod_exit(void)
{
    nf_unregister_hook(&nf_incoming);
    nf_unregister_hook(&nf_outgoing);
    pr_info("[*] FireWall unload !\n");
}
