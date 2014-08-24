#include <stdio.h>
#include <check.h>
#include <carp_machine.h>

START_TEST(test_instr_add)
{
	carp_machine_state m;
	carp_vm_init(&m, 10, 0);
	carp_stack_push(&m.stack, 2);
	carp_stack_push(&m.stack, 3);
	carp_instr_ADD(&m);
	long long val;
	int ret = carp_stack_peek(&m.stack, &val);
	ck_assert_msg(ret == 0, "Stack peek failed, returned: %d", ret);
	ck_assert_msg(val == 5, "Expected: 5, got: %llu!", val);
}
END_TEST

Suite *instr_suite(void) {
	Suite *suite = suite_create("carp");
	TCase *tcase = tcase_create("instr_add");
	tcase_add_test(tcase, test_instr_add);
	suite_add_tcase(suite, tcase);
	return suite;
}

int main(int arg, char *argv[]) {
	int failed = 0;
	Suite *suite = instr_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_VERBOSE);
	failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return failed;
}
