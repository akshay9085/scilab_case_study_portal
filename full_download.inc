<?php
// $Id$
function scilab_case_study_download_full_project()
{
	global $user;
	$id = arg(3);
	$root_path = scilab_case_study_path();
	//var_dump($root_path);die;
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('id', $id);
	$case_study_q = $query->execute();
	$case_study_data = $case_study_q->fetchObject();
	$CASE_STUDY_PATH = $case_study_data->directory_name . '/project_files/';
	/* zip filename */
	$zip_filename = $root_path . 'zip-' . time() . '-' . rand(0, 999999) . '.zip';
	/* creating zip archive on the server */
	$zip = new ZipArchive();
	$zip->open($zip_filename, ZipArchive::CREATE);
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('id', $id);
	$circuit_simulation_udc_q = $query->execute();
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('id', $id);
	$query = db_select('case_study_submitted_abstracts_file');
	$query->fields('case_study_submitted_abstracts_file');
	$query->condition('proposal_id', $id);
	$project_files = $query->execute();
	while ($scilab_project_files = $project_files->fetchObject()) {
		$zip->addFile($root_path . $CASE_STUDY_PATH . $scilab_project_files->filepath, $CASE_STUDY_PATH . str_replace(' ', '_', basename($scilab_project_files->filename)));
	}
	$zip_file_count = $zip->numFiles;
	$zip->close();
	if ($zip_file_count > 0) {
		if ($user->uid) {
			/* download zip file */
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $case_study_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			ob_end_flush();
			ob_clean();
			flush();
			readfile($zip_filename);
			unlink($zip_filename);
		} //$user->uid
		else {
			header('Content-Type: application/zip');
			header('Content-disposition: attachment; filename="' . str_replace(' ', '_', $case_study_data->project_title) . '.zip"');
			header('Content-Length: ' . filesize($zip_filename));
			header("Content-Transfer-Encoding: binary");
			header('Expires: 0');
			header('Pragma: no-cache');
			ob_end_flush();
			ob_clean();
			flush();
			readfile($zip_filename);
			unlink($zip_filename);
		}
	} //$zip_file_count > 0
	else {
		drupal_set_message("There are no case study project in this proposal to download", 'error');
		drupal_goto('circuit-simulation-project/full-download/project');
	}
}